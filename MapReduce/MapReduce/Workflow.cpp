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
// ===============================================================================

// Local Headers
#include "Workflow.h"
#include "FileManagement.h"
#include "Map.h"
#include "Sorter.h"
#include "Reduce.h"
#include <boost/algorithm/string.hpp>

using namespace std;

// -----------------------------------------------
// Constructor
// -----------------------------------------------
Workflow::Workflow()
{
    _pMap = std::make_unique<Map>();
    _pSorter = std::make_unique<Sorter>();
    _pReduce = std::make_unique<Reduce>();
}

// -----------------------------------------------
// Destructor
// -----------------------------------------------
Workflow::~Workflow() {}

// -------------------------------------------------------------------------------
// run
// -------------------------------------------------------------------------------
void Workflow::run(string inputFileDir, string outputFileDir, string tempOutputFileDir)
{
    map(inputFileDir, tempOutputFileDir);
    //list<string> sortResults = sort(outputFileName);
    //reduce(sortResults);
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
list<string> Workflow::sort(string fileName)
{
    list<string> lstOfData = _pSorter->sort(fileName);
    return lstOfData;
}

// -------------------------------------------------------------------------------
// reduce
// -------------------------------------------------------------------------------
void Workflow::reduce(list<string> lstOfData)
{
    list<string> DataToWriteToFile;

    // preview what's in the file
    for (string lst : lstOfData)
    {
        //cout << "lstOfdata: " << lst << endl;

        // Get key from the list value
        Map map;
        string sKey = map.getKey(lst);

        // Get the key value
        list<int> itr = map.getKeyValue(sKey, lstOfData);
        _pReduce->reduceFunc(sKey, itr);
    }

    // other functions to process and export data
    DataToWriteToFile = _pReduce->GetData();
    _pReduce->exportFunc(DataToWriteToFile);
}