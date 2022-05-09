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
// 5/07/22 - Cliford - Added the Dll library for the reduce capability.
// ===============================================================================

//#undef _HAS_STD_BYTE
#define _HAS_STD_BYTE 0

// Local Headers
#include "Workflow.h"
#include "FileManagement.h"
#include "Map.h"
#include "Sorter.h"
#include "Reduce.h"
#include "ReduceLibrary.h"
#include <boost/algorithm/string.hpp>
#include <glog/logging.h>
#include <set>
#include <windows.h>

using namespace std;

// for debugging purposes change to 0 to 
// not show cout messages in the cmd line
#define debug 0

// dll map functions
typedef int (*reduceFunction)(string, list<int>);
typedef int (*exportFunction)(list<string>, string);
typedef list<string> (*GetDataFunction)();

reduceFunction dllReduceFunc;
exportFunction dllExportReduceFunc;
GetDataFunction dllGetData;

namespace MapReduce
{
    // -----------------------------------------------
    // Constructor
    // -----------------------------------------------
    Workflow::Workflow()
    {
        setupReduceDLL();
        _pMap = new Map();
        _pSorter = new Sorter();
        _pReduce = new Reduce();
        _pFileManagement = new FileManagement();
    }

    // -------------------------------------------------------------------------------
    // Overloaded Constructor
    // -------------------------------------------------------------------------------
    Workflow::Workflow(FileManagement* _pFM, Map* _pM, Sorter* _pS, Reduce* _pR)
    {
        _pFileManagement = _pFM;
        _pMap = _pM;
        _pSorter = _pS;
        _pReduce = _pR;
    }

    // -----------------------------------------------
    // Destructor
    // -----------------------------------------------
    Workflow::~Workflow()
    {
        delete _pMap;
        delete _pSorter;
        delete _pReduce;
        delete _pFileManagement;
        LOG(INFO) << "Workflow component destroyed";
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
                dllGetData = (GetDataFunction)GetProcAddress(hDLL, "GetData");
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
            cout << "About to run sort function" << endl;
        sort(tempOutputFileDir);

        if (debug)
            cout << "About to run reduce function" << endl;
        reduce(tempOutputFileDir, outputFileDir);

       // _pFileManagement->clearDirectory(tempOutputFileDir);
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
                    // read the input file contents
                    list<string> fileContents = _pFileManagement->readFile(inputFileName);

                    // if no contents in file, do not proceed with mapping
                    if (fileContents.size() <= 0)
                    {
                        return inputFiles;
                    }

                    // get contents of file as one string
                    string fileContentsStr;
                    for (string s : fileContents)
                    {
                        fileContentsStr += s + " ";
                    }

                    // count the frequencies of the words in input file
                    std::multimap<string, int> wordFreqs = _pMap->map(inputFileName, fileContentsStr);

                    // if the output dir does not end in backslash, add one and use to generate full path of temp output file
                    boost::trim_right(tempOutputFileDir);
                    if (tempOutputFileDir.back() != '\\')
                    {
                        tempOutputFileDir += "\\";
                    }
                    string outputFileName = tempOutputFileDir + _pFileManagement->getFileName(inputFileName) + "-tempOutput.txt";

                    // write the words and frequencies to output file in the temp directory
                    _pMap->exportMap(outputFileName, wordFreqs);
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
    // sort
    // -------------------------------------------------------------------------------
    int Workflow::sort(string tempDirectory)
    {
        LOG(INFO) << "Workflow.sort -- BEGIN";
        cout << "Sorting..." << endl;

        // Local variables
        string fileName = "";
        list<string> lstOfData;

        // get the list of all the files in the temp folder
        list<string> tempFiles = _pFileManagement->getTextFilesInDirectory(tempDirectory);

        // Loop through each files 
        for (string file : tempFiles)
        {
            fileName = file;
            _pSorter->sort(fileName);
        }

        cout << "Finished sorting" << endl;
        LOG(INFO) << "Workflow.sort -- END";

        // return
        return 0;
    }

    // -------------------------------------------------------------------------------
    // reduce
    // -------------------------------------------------------------------------------
    void Workflow::reduce(string tempDirectory, string outputFileDir)
    {
        LOG(INFO) << "Workflow.reduce -- BEGIN";
        cout << "Reducing..." << endl;

        // Local Varibles
        string fileName = "";
        list<string> DataToWriteToFile;
        list<string> fileData;

        // get list of all files in input file directory
        list<string> tempFiles = _pFileManagement->getTextFilesInDirectory(tempDirectory);

        for (string file : tempFiles)
        {
            // adding all the data from every single file into just one list
            fileName = file;
            list<string> sData;
            sData = _pFileManagement->readFile(fileName);
            fileData.insert(fileData.end(), sData.begin(), sData.end());

            if(debug)
                cout << "File Data size: " << fileData.size() << endl;
        }
        
        // keep track of already processed data as to not process again
        set<string> processedKeys;
        int rowsToSkip = 0;

        // go through file data
        for (string lstString : fileData)
        {
            // Get key from the list value
            string sKey = _pMap->getKey(lstString);

            // if key already reduced, do not reduce again
            if (processedKeys.count(sKey) > 0) 
            {
                continue;
            }

            // Get the key value
            list<int> itr = _pMap->getKeyValue(sKey, fileData, rowsToSkip);

            // reduce older code
            //_pReduce->reduceFunc(sKey, itr);
            
            // new code with DLL
            dllReduceFunc(sKey, itr);

            processedKeys.insert(sKey);
            rowsToSkip += itr.size();
        }

        // get the data to write to a new file
        
        // Older code
        //DataToWriteToFile = _pReduce->GetData();        
        
        // new code with dll
        DataToWriteToFile = dllGetData();

        // sort it
        DataToWriteToFile.sort();

        // passed into exportFunc for processing
        cout << "Exporting reduced data..." << endl;

        // Older code
        //_pReduce->exportFunc(DataToWriteToFile, outputFileDir);

        // new code with DLL
        dllExportReduceFunc(DataToWriteToFile, outputFileDir);

        // write the empty success file as per project requirements
        _pFileManagement->createSuccessFile(outputFileDir);

        // clear temp output directory now that we are done with the files
        _pFileManagement->clearDirectory(tempDirectory);

        cout << "Finished reducing" << endl;
        LOG(INFO) << "Workflow.reduce -- END";
    }
}