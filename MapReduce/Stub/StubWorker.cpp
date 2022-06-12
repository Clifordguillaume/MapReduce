// ===============================================================================
// CSE 687 MapReduce Project
// 
// StubWorker.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The StubWorker contains the main file to execute for each stub
// 
// File History:
// 6/9/22 - Elizabeth - Initial file. Created handleMessage() with map handling,
//                      isDoneExecuting(), markDone()
// 6/11/22 - Elizabeth - Moved methods from MapReduce Workflow to this file
// ===============================================================================
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <winsock2.h>
#include "StringUtils.h"
#include "FileManagement.h"
#include "MapLibrary.h"
#include "ReduceLibrary.h"
#include "Sorter.h"
#include "KeyValUtils.h"
#include "ConcurrentHashMap.h"
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <glog/logging.h>
#include <set>
#include <windows.h>
#include <iostream>
#include "StubWorker.h"
#include <vector>

namespace Stub
{
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

    // -------------------------------------------------------------------------------
    // Constructor
    // -------------------------------------------------------------------------------
    StubWorker::StubWorker()
    {
        _pSorter = new Sorter();
        _pFileManagement = new FileManagement();
    }

    // -------------------------------------------------------------------------------
    // Destructor
    // -------------------------------------------------------------------------------
    StubWorker::~StubWorker()
    {
        delete _pSorter;
        delete _pFileManagement;
    }

    // -------------------------------------------------------------------------------
    // handleMessage
    // -------------------------------------------------------------------------------
    void StubWorker::handleMessage(string msg)
    {
        // received command, not "done" yet
        done = false;

        // parse the message if it is not empty
        vector<string> msgContents = StringUtils::parseMessage(msg);
        if (msgContents.size() < 4)
        {
            cout << "Message does not have enough information" << endl;
            return;
        }
        command = msgContents[0];
        inputFileDir = msgContents[1];
        outputFileDir = msgContents[2];
        tempOutputFileDir = msgContents[3];

        // determine what command was issued and act accordingly
        int cmd = stoi(command);
        if (cmd == 0)  // map
        {
            cout << "Received MAP command from controller. " << endl;
            cout << "InputFileDir: " << inputFileDir << endl;
            cout << "TempOutputFileDir: " << tempOutputFileDir << endl;
            cout << "Mapping..." << endl;

            // create func pointer to callback and mark the done flag when map() in StubWorker has completed
            boost::function<void(StubWorker*)> fnc_ptr = boost::bind(&StubWorker::markDone, _1);
            map(inputFileDir, tempOutputFileDir, fnc_ptr, this);
        }
        else if (cmd == 1)  // reduce]
        {
            cout << "Received REDUCE command from controller. Mapping..." << endl;

            // TODO: create reduce callback similar to map
            reduce(tempOutputFileDir, outputFileDir);
        }
        else { // unknown command
            cout << "Unknown command received from controller. Command code: " << command << endl;
        }
    }

    // -------------------------------------------------------------------------------
    // markDone
    // -------------------------------------------------------------------------------
    void StubWorker::markDone()
    {
        done = true;
    }

    // -------------------------------------------------------------------------------
    // isDoneExecuting
    // -------------------------------------------------------------------------------
    bool StubWorker::isDoneExecuting()
    {
        return done;
    }

    // -------------------------------------------------------------------------------
    // setupMapDLL
    // -------------------------------------------------------------------------------
    void StubWorker::setupMapDLL()
    {
        LOG(INFO) << "StubWorker.setupMapDLL -- BEGIN";
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
            LOG(ERROR) << "StubWorker.setupMapDLL -- Exception setting up MapLibrary DLL";
            LOG(ERROR) << e.what();
        }
        LOG(INFO) << "StubWorker.setupMapDLL -- END";
    }

    // -------------------------------------------------------------------------------
    // setupReduceDLL
    // -------------------------------------------------------------------------------
    void StubWorker::setupReduceDLL()
    {
        LOG(INFO) << "StubWorker.setupReduceDLL -- BEGIN";
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
            LOG(ERROR) << "StubWorker.setupReduceDLL -- Exception setting up ReduceLibrary DLL";
            LOG(ERROR) << e.what();
        }
        LOG(INFO) << "StubWorker.setupReduceDLL -- END";
    }

    // -------------------------------------------------------------------------------
    // map
    // -------------------------------------------------------------------------------
    list<string> StubWorker::map(string inputFileDir, string tempOutputFileDir, boost::function<void(StubWorker*)> callback, StubWorker* worker)
    {
        LOG(INFO) << "StubWorker.map -- BEGIN";

        list<string> inputFiles;
        try
        {
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
            LOG(ERROR) << "StubWorker.map -- Exception mapping";
            LOG(ERROR) << e.what();
        }

        LOG(INFO) << "StubWorker.map -- END";

        // signal map is done
        if (callback != NULL && worker != NULL)
        {
            callback(worker);
        }

        return inputFiles;
    }

    // -------------------------------------------------------------------------------
    // mapThreadData
    // -------------------------------------------------------------------------------
    void StubWorker::mapThreadData(string inputFileName, string tempOutputFileDir)
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
    void StubWorker::reduce(string tempDirectory, string outputFileDir)
    {
        LOG(INFO) << "StubWorker.reduce -- BEGIN";

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

        LOG(INFO) << "StubWorker.reduce -- END";
    }

    // -------------------------------------------------------------------------------
    // reduceFile
    // -------------------------------------------------------------------------------
    void StubWorker::reduceFile(string file)
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
    void StubWorker::saveReducedData(string outputFileDir)
    {
        // loop through hashmap and add data to file
        list<string> mapContents = ConcurrentHashMap::getMapContents();

        // sort it
        mapContents.sort();

        // Export the map contents to the user-defined output file dir
        dllExportReduceFunc(mapContents, outputFileDir);

        // write the empty success file as per project requirements
        _pFileManagement->createSuccessFile(outputFileDir);
    }
}
