// ===============================================================================
// CSE 687 MapReduce Project
// 
// Workflow.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The Workflow handles the mapping, sorting, and reducing of data
//              received from the user from the Executive.
//              
// 
// File History:
// 4/14/22 - Elizabeth - Move run(), map(), sort(), reduce() from Executive to 
//                       Workflow. Modify map() to traverse input directory and
//                       write to temp output directory.
// 4/19/22 - Elizabeth - Change FileManagement, Map, Sorter, Reduce to pointers
// 4/20/22 - Elizabeth - Make map, sorter, reduce, filemanagement pointers.
//                       Constructor. Desctructor. Add namespace
// 4/24/22 - Cliford - Fixed the reduce function to show the correct reduced data
//                    added the debug macro for debugging purposes
// 4/24/22 - Elizabeth - Add glogs, add check for empty string in map function,
//                       clear temp output file dir before new export
// 4/25/22 - Elizabeth - Add check for already processed words in reduce function.
//                       Add cout logs to display progress to user
// 5/7/22 - Elizabeth - Convert map() to use MapLibrary DLL
// 5/7/22 - Cliford - Added the Dll library for the reduce capability.
// 5/8/22 - Elizabeth - Add MapLibrary DLL explicit call
// 5/9/22 - Cliford - Add ReduceLibrary DLL explicit call. Add getKeyValue 
//                    MapLibrary func
// 5/11/22 - Elizabeth - Rework getKeyValue MapLibrary func to use new KeyValues
//                      struct. Add getKey. Use ReducedData struct for reduced data 
//                      return from ReduceLibrary. Modify reduce() accordingly.
// 5/22/22 - Elizabeth - Use KeyValUtils. Use ConcurrentHashMap. 
//                      Utilize threads in reduce()
// 5/23/22 - Cliford - I added the mapThreadData function to be called by the 
//                     Thread to process the map functionality
// 6/9/22 - Elizabeth - Added callback to map() for StubWorker
// ===============================================================================

//#undef _HAS_STD_BYTE
#define _HAS_STD_BYTE 0


// Local Headers
#include "Workflow.h"
#include "FileManagement.h"
#include "MapLibrary.h"
#include "ReduceLibrary.h"
#include "KeyValUtils.h"
#include "ConcurrentHashMap.h"
#include <boost/algorithm/string.hpp>
#include <boost/function.hpp>
#include <glog/logging.h>
#include <set>
#include <windows.h>

using namespace std;

// for debugging purposes change to 0 to 
// not show cout messages in the cmd line
#define debug 0

// dll map functions
typedef WordCount* (*funcMap)(string, string, int*);
typedef void (*funcExportMap)(string, WordCount*, int);
funcMap dllMapFunc;
funcExportMap dllExportMapFunc;

// dll Reduce functions
typedef ReducedData(*reduceFunction)(string, list<int>);
typedef int (*exportFunction)(list<string>, string);
reduceFunction dllReduceFunc;
exportFunction dllExportReduceFunc;

namespace MapReduce
{
    // -----------------------------------------------
    // Constructor
    // -----------------------------------------------
    Workflow::Workflow()
    {
        setupMapDLL();
        setupReduceDLL();
        _pSorter = new Sorter();
        _pFileManagement = new FileManagement();
    }

    // -------------------------------------------------------------------------------
    // Overloaded Constructor
    // -------------------------------------------------------------------------------
    Workflow::Workflow(FileManagement* _pFM, Map* _pM, Sorter* _pS, Reduce* _pR)
    {
        _pFileManagement = _pFM;
        _pSorter = _pS;
    }

    // -----------------------------------------------
    // Destructor
    // -----------------------------------------------
    Workflow::~Workflow()
    {
        delete _pSorter;
        delete _pFileManagement;
        LOG(INFO) << "Workflow component destroyed";
    }

    // -------------------------------------------------------------------------------
    // setupMapDLL
    // -------------------------------------------------------------------------------
    void Workflow::setupMapDLL()
    {
        LOG(INFO) << "Workflow.setupMapDLL -- BEGIN";
        try
        {
            HINSTANCE hDLL;

            const wchar_t* libName = L"MapLibrary";

            hDLL = LoadLibraryEx(libName, NULL, NULL);   // Handle to DLL

            if (hDLL != NULL) {

                dllMapFunc = (funcMap)GetProcAddress(hDLL, "mapFunc");
                dllExportMapFunc = (funcExportMap)GetProcAddress(hDLL, "exportMap");
            }
        }
        catch (exception e)
        {
            LOG(ERROR) << "Workflow.setupMapDLL -- Exception setting up MapLibrary DLL";
            LOG(ERROR) << e.what();
        }
        LOG(INFO) << "Workflow.setupMapDLL -- END";
    }

    // -------------------------------------------------------------------------------
    // setupReduceDLL
    // -------------------------------------------------------------------------------
    void Workflow::setupReduceDLL()
    {
        LOG(INFO) << "Workflow.setupReduceDLL -- BEGIN";
        try
        {
            HINSTANCE hDLL;

            const wchar_t* libName = L"ReduceLibrary";
            hDLL = LoadLibraryEx(libName, NULL, NULL);   // Handle to DLL

            if (hDLL != NULL) {
                dllReduceFunc = (reduceFunction)GetProcAddress(hDLL, "reduceFunc");
                dllExportReduceFunc = (exportFunction)GetProcAddress(hDLL, "exportFunc");
            }
        }
        catch (exception e)
        {
            LOG(ERROR) << "Workflow.setupReduceDLL -- Exception setting up ReduceLibrary DLL";
            LOG(ERROR) << e.what();
        }
        LOG(INFO) << "Workflow.setupReduceDLL -- END";
    }

    // -------------------------------------------------------------------------------
    // run
    // -------------------------------------------------------------------------------
    void Workflow::run(string inputFileDir, string outputFileDir, string tempOutputFileDir)
    {
        if (debug)
            cout << "About to run map function" << endl;
        list<string> mappedFiles = map(inputFileDir, tempOutputFileDir);

        if (mappedFiles.size() <= 0) 
        {
            LOG(INFO) << "No input files found. Not proceeding with sort or reduce.";
            return;
        }

        if (debug)
            cout << "About to run reduce function" << endl;
        reduce(tempOutputFileDir, outputFileDir);
    }

    // -------------------------------------------------------------------------------
    // map
    // -------------------------------------------------------------------------------
    list<string> Workflow::map(string inputFileDir, string tempOutputFileDir)
    {
        LOG(INFO) << "Workflow.map -- BEGIN";
        cout << "Mapping..." << endl;
        if (debug)
            cout << "inside the map function" << endl;

        list<string> inputFiles;
        try
        {
            // clear all files in the temp output directory before exporting new map files
            list<string> currTempOutputFiles = _pFileManagement->getTextFilesInDirectory(tempOutputFileDir);
            for (string tempOutputFileName : currTempOutputFiles)
            {
                _pFileManagement->removeFile(tempOutputFileName);
            }

            // get list of all files in input file directory
            inputFiles = _pFileManagement->getTextFilesInDirectory(inputFileDir);

            if (inputFiles.size() > 0)
            {
                for (string inputFileName : inputFiles)
                {
                    std::thread t([this, inputFileName, tempOutputFileDir] { this->mapThreadData(inputFileName, tempOutputFileDir); });
                    t.join();
                }
            }
        }
        catch (exception e)
        {
            LOG(ERROR) << "Workflow.map -- Exception mapping";
            LOG(ERROR) << e.what();
        }

        cout << "Finished mapping" << endl;
        LOG(INFO) << "Workflow.map -- END";

        return inputFiles;
    }

    // -------------------------------------------------------------------------------
    // mapThreadData
    // -------------------------------------------------------------------------------
    void Workflow::mapThreadData(string inputFileName, string tempOutputFileDir)
    {
        // read the input file contents
        list<string> fileContents = _pFileManagement->readFile(inputFileName);

        // if no contents in file, do not proceed with mapping
        if (fileContents.size() <= 0)
        {
            return;
        }

        // get contents of file as one string
        string fileContentsStr;
        for (string s : fileContents)
        {
            fileContentsStr += s + " ";
        }

        // count the frequencies of the words in input file
        int numWords = 0;
        WordCount* wordFreqs = dllMapFunc(inputFileName, fileContentsStr, &numWords);

        // if the output dir does not end in backslash, add one and use to generate full path of temp output file
        boost::trim_right(tempOutputFileDir);
        if (tempOutputFileDir.back() != '\\')
        {
            tempOutputFileDir += "\\";
        }
        string outputFileName = tempOutputFileDir + _pFileManagement->getFileName(inputFileName) + "-tempOutput.txt";

        // write the words and frequencies to output file in the temp directory
        dllExportMapFunc(outputFileName, wordFreqs, numWords);
    }

    // -------------------------------------------------------------------------------
    // reduce
    // -------------------------------------------------------------------------------
    void Workflow::reduce(string tempDirectory, string outputFileDir)
    {
        LOG(INFO) << "Workflow.reduce -- BEGIN";
        cout << "Reducing..." << endl;

        // get list of all files in input file directory
        list<string> tempFiles = _pFileManagement->getTextFilesInDirectory(tempDirectory);

        // reduce all data in each temp file
        for (string file : tempFiles)
        {
            std::thread t([this, file] { this->reduceFile(file); });
            t.join();
        }

        // export the reduced data
        saveReducedData(outputFileDir);

        // clear temp output directory now that we are done with the files
        _pFileManagement->clearDirectory(tempDirectory);

        cout << "Finished reducing" << endl;
        LOG(INFO) << "Workflow.reduce -- END";
    }

    // -------------------------------------------------------------------------------
    // reduceFile
    // -------------------------------------------------------------------------------
    void Workflow::reduceFile(string file)
    {
        // sort the contents of the temp file
        _pSorter->sort(file);

        // read the contents of the temp file
        list<string> fileContents = _pFileManagement->readFile(file);

        // keep track of already processed data as to not process again
        set<string> processedKeys;
        int rowsToSkip = 0;

        // go through file data
        for (string lstString : fileContents)
        {
            // Get key from the list value
            string sKey = KeyValUtils::getKey(lstString);

            // if key already reduced, do not reduce again
            if (processedKeys.count(sKey) > 0)
            {
                continue;
            }

            // Get the key value
            list<int> keyValsList = KeyValUtils::getKeyValues(sKey, fileContents, rowsToSkip);

            // new code with DLL
            ReducedData reducedData = dllReduceFunc(sKey, keyValsList);

            // add reduced data to static map
            ConcurrentHashMap::addToMap(reducedData);

            processedKeys.insert(sKey);
            rowsToSkip += keyValsList.size();
        }
    }

    // -------------------------------------------------------------------------------
    // saveReducedData
    // -------------------------------------------------------------------------------
    void Workflow::saveReducedData(string outputFileDir)
    {
        // loop through hashmap and add data to file
        list<string> mapContents = ConcurrentHashMap::getMapContents();

        // sort it
        mapContents.sort();

        cout << "Exporting reduced data..." << endl;

        // Export the map contents to the user-defined output file dir
        dllExportReduceFunc(mapContents, outputFileDir);

        // write the empty success file as per project requirements
        _pFileManagement->createSuccessFile(outputFileDir);
    }
}