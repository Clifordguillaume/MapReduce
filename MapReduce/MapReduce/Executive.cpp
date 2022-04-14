// ===============================================================================
// CSE 687 MapReduce Project
// 
// Executive.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: This Executive class handles all primary steps in the Map-Reduce 
//				program based on user input via command line.
//              
// 
// File History:
// 4/10/22 - Elizabeth - Moved main functions into new run method and decouple 
//			             map and file manager
// 4/13/22 - Elizabeth - MOVED sort and reduce functions from main to Executive
// 4/13/22 - Elizabeth - Condense run() into separate map(), sort(), reduce(). 
//                       Remove writeMapOutput()
// ===============================================================================

// Local Headers
#include "Executive.h"
#include "FileManagement.h"
#include "Map.h"
#include "Sorter.h"
#include "Reduce.h"

using namespace std;

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
Executive::Executive()
{
}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
Executive::~Executive() 
{
}

// -------------------------------------------------------------------------------
// run
// -------------------------------------------------------------------------------
void Executive::run(string inputFileName, string outputFileName)
{
    map(inputFileName, outputFileName);
    list<string> sortResults = sort(outputFileName);
    reduce(sortResults);
}

// -------------------------------------------------------------------------------
// map
// -------------------------------------------------------------------------------
void Executive::map(string inputFileName, string outputFileName)
{
    // read the input file contents
    list<string> fileContents = fileManager.readFile(inputFileName);

    // TODO: Remove this loop and write each fileContents to new temp output file
    string fileContentsStr;
    for(string s : fileContents) 
    {
        fileContentsStr += s + " ";
    }

    // count the frequencies of the words in input file
    std::map<string, int> wordFreqs = mapper.map(inputFileName, fileContentsStr);

    // write the words and frequencies to output file
    mapper.exportMap(outputFileName, wordFreqs);
}

// -------------------------------------------------------------------------------
// sort
// -------------------------------------------------------------------------------
list<string> Executive::sort(string fileName)
{
    Sorter sortingclass;
    list<string> lstOfData = sortingclass.sort(fileName);
    return lstOfData;
}

// -------------------------------------------------------------------------------
// reduce
// -------------------------------------------------------------------------------
void Executive::reduce(list<string> lstOfData)
{
    Reduce reduce;
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
        reduce.reduceFunc(sKey, itr);
    }

    // other functions to process and export data
    DataToWriteToFile = reduce.GetData();
    reduce.exportFunc(DataToWriteToFile);
}