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
// ===============================================================================

// Local Headers
#include "Workflow.h"
#include "FileManagement.h"
#include "Map.h"
#include "Sorter.h"
#include "Reduce.h"
#include <boost/algorithm/string.hpp>

using namespace std;

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
    }

    // -------------------------------------------------------------------------------
    // run
    // -------------------------------------------------------------------------------
    void Workflow::run(string inputFileDir, string outputFileDir, string tempOutputFileDir)
    {
        map(inputFileDir, tempOutputFileDir);

        sort(tempOutputFileDir);

        reduce(tempOutputFileDir);
    }

    // -------------------------------------------------------------------------------
    // map
    // -------------------------------------------------------------------------------
    void Workflow::map(string inputFileDir, string tempOutputFileDir)
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

    // -------------------------------------------------------------------------------
    // sort
    // -------------------------------------------------------------------------------
    int Workflow::sort(string tempDirectory)
    {
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

        // return
        return 0;
    }

    // -------------------------------------------------------------------------------
    // reduce
    // -------------------------------------------------------------------------------
    void Workflow::reduce(string tempDirectory)
    {
        // Local Varibles
        string fileName = "";
        list<string> DataToWriteToFile;
        list<string> fileData;

        // get list of all files in input file directory
        list<string> tempFiles = _pFileManagement->getFilesInDirectory(tempDirectory);

        for (string file : tempFiles)
        {
            fileName = file;
            fileData = _pFileManagement->readFile(fileName);

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

                // other functions to process and export data
                DataToWriteToFile = _pReduce->GetData();
                _pReduce->exportFunc(DataToWriteToFile);
            }
        }
    }
}