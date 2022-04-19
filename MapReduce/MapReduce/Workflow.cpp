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

    sort(tempOutputFileDir);

    reduce(tempOutputFileDir);
}

// -------------------------------------------------------------------------------
// map
// -------------------------------------------------------------------------------
void Workflow::map(string inputFileDir, string tempOutputFileDir)
{
    // get list of all files in input file directory
    list<string> inputFiles = fileManager.getFilesInDirectory(inputFileDir);

    for (string inputFileName : inputFiles) 
    {
        // read the input file contents
        list<string> fileContents = fileManager.readFile(inputFileName);

        // get contents of file as one string
        string fileContentsStr;
        for (string s : fileContents)
        {
            fileContentsStr += s + " ";
        }

        // count the frequencies of the words in input file
        std::multimap<string, int> wordFreqs = mapper.map(inputFileName, fileContentsStr);

        // if the output dir does not end in backslash, add one and use to generate full path of temp output file
        boost::trim_right(tempOutputFileDir);
        if (tempOutputFileDir.back() != '\\')
        {
            tempOutputFileDir += "\\";
        }
        string outputFileName = tempOutputFileDir + fileManager.getFileName(inputFileName) + "-tempOutput.txt";

        // write the words and frequencies to output file in the temp directory
        mapper.exportMap(outputFileName, wordFreqs);
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

    // class instantiation
    Sorter sortingclass;

    // get the list of all the files in the temp folder
    list<string> tempFiles = fileManager.getFilesInDirectory(tempDirectory);

    // Loop through each files 
    for (string file : tempFiles) 
    {
        fileName = file;
        sortingclass.sort(fileName);
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

    // class instantiation
    Reduce reduce;

    // get list of all files in input file directory
    list<string> tempFiles = fileManager.getFilesInDirectory(tempDirectory);

    for (string file : tempFiles) 
    {
        fileName = file;
        fileData = fileManager.readFile(fileName);

        // preview what's in the file
        for (string lstString : fileData)
        {
            //cout << "lstOfdata: " << lst << endl;

            // Get key from the list value
            Map map;
            string sKey = map.getKey(lstString);

            // Get the key value
            list<int> itr = map.getKeyValue(sKey, fileData);
            reduce.reduceFunc(sKey, itr);

            // other functions to process and export data
            DataToWriteToFile = reduce.GetData();
            reduce.exportFunc(DataToWriteToFile);
        }
    }
}