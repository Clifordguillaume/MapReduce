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
// 4/24/23 - Cliford - Fixed the reduce function to show the correct reduced data
//                    added the debug macro for debugging purposes
// 4/24/23 - Elizabeth - Add glogs
// ===============================================================================

// Local Headers
#include "Workflow.h"
#include "FileManagement.h"
#include "Map.h"
#include "Sorter.h"
#include "Reduce.h"
#include <boost/algorithm/string.hpp>
#include <glog/logging.h>

using namespace std;

// for debugging purposes change to 0 to 
// not show cout messages in the cmd line
#define debug 0

namespace MapReduce
{
    // -----------------------------------------------
    // Constructor
    // -----------------------------------------------
    Workflow::Workflow()
    {
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
    // run
    // -------------------------------------------------------------------------------
    void Workflow::run(string inputFileDir, string outputFileDir, string tempOutputFileDir)
    {
        if (debug)
            cout << "About to run map function" << endl;
        map(inputFileDir, tempOutputFileDir);

        if (debug)
            cout << "About to run sort function" << endl;
        sort(tempOutputFileDir);

        if (debug)
            cout << "About to run reduce function" << endl;
        reduce(tempOutputFileDir);

       // _pFileManagement->clearDirectory(tempOutputFileDir);
    }

    // -------------------------------------------------------------------------------
    // map
    // -------------------------------------------------------------------------------
    void Workflow::map(string inputFileDir, string tempOutputFileDir)
    {
        LOG(INFO) << "Workflow.map -- BEGIN";
        if (debug)
            cout << "inside the map function" << endl;

        try 
        {
            // get list of all files in input file directory
            list<string> inputFiles = _pFileManagement->getFilesInDirectory(inputFileDir);

            for (string inputFileName : inputFiles)
            {
                // read the input file contents
                list<string> fileContents = _pFileManagement->readFile(inputFileName);

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
        catch (exception e)
        {
            LOG(ERROR) << "Workflow.map -- Exception mapping";
            LOG(ERROR) << e.what();
        }
    }

    // -------------------------------------------------------------------------------
    // sort
    // -------------------------------------------------------------------------------
    int Workflow::sort(string tempDirectory)
    {
        LOG(INFO) << "Workflow.sort -- BEGIN";
        // Local variables
        string fileName = "";
        list<string> lstOfData;

        // get the list of all the files in the temp folder
        list<string> tempFiles = _pFileManagement->getFilesInDirectory(tempDirectory);

        // Loop through each files 
        for (string file : tempFiles)
        {
            fileName = file;
            _pSorter->sort(fileName);
        }

        LOG(INFO) << "Workflow.sort -- END";

        // return
        return 0;
    }

    // -------------------------------------------------------------------------------
    // reduce
    // -------------------------------------------------------------------------------
    void Workflow::reduce(string tempDirectory)
    {
        LOG(INFO) << "Workflow.reduce -- BEGIN";

        // Local Varibles
        string fileName = "";
        list<string> DataToWriteToFile;
        list<string> fileData;

        // get list of all files in input file directory
        list<string> tempFiles = _pFileManagement->getFilesInDirectory(tempDirectory);

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

        // preview what's in the file
        for (string lstString : fileData)
        {
            //cout << "lstOfdata: " << lst << endl;

            // Get key from the list value
            Map map;
            string sKey = map.getKey(lstString);

            // Get the key value
            list<int> itr = map.getKeyValue(sKey, fileData);
            _pReduce->reduceFunc(sKey, itr);
        }

        // get the data to write to a new file
        DataToWriteToFile = _pReduce->GetData();

        // sort it
        DataToWriteToFile.sort();

        // remove duplicates
        DataToWriteToFile.unique();

        // passed into exportFunc for processing
        _pReduce->exportFunc(DataToWriteToFile);

        LOG(INFO) << "Workflow.reduce -- END";
    }
}