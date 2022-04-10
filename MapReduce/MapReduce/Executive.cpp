// ===============================================================================
// CSE 687 MapReduce Project
// 
// Executive.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: 
//              
// 
// File History:
// 4/10/22 - Elizabeth - Moved main functions into new run method and decouple map and file manager
// 
// ===============================================================================

// Local Headers
#include "Executive.h";
#include "FileManagement.h";
#include "Map.h";

using namespace std;

// -----------------------------------------------
// Constructor
// -----------------------------------------------
Executive::Executive()
{
}

// -----------------------------------------------
// Destructor
// -----------------------------------------------
Executive::~Executive() 
{
}

/**
 * Run
 * @input inputFileName - name of input file to read from
 * @input outputFileName - name of file to write results to
 */
void Executive::run(string inputFileName, string outputFileName)
{
    // read the input file contents
    string fileContents = fileManager.parseFile(inputFileName);

    // count the frequencies of the words in input file
	std::map<string, int> wordFreqs = map.map(inputFileName, fileContents);

	// write entries in map to file
	writeMapOutput(outputFileName, wordFreqs);
}

/**
 * Writes a map contents to a specified file
 * @param outputFileName - name of file to write to
 * @param mapToWrite - the map of data to write
 */
void Executive::writeMapOutput(string outputFileName, std::map<string, int> mapToWrite) 
{
	// write entries in map to file
	std::map<string, int>::iterator it;
	for (it = mapToWrite.begin(); it != mapToWrite.end(); it++)
	{
		string key = it->first;
		int value = it->second;
		fileManager.writeKeyValueToFile(outputFileName, key, value);
	}
}