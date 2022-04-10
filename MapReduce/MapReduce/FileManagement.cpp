// ===============================================================================
// CSE 687 MapReduce Project
// 
// FileManagement.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: 
// 
// 
// Notes:
// 
// File History:
// 4/8/22 - Elizabeth - Added parseFile, writeKeyValueToFile
// 4/9/22 - Elizabeth - Change format of output file strings
// ===============================================================================

// Local Headers
#include "FileManagement.h"
#include <fstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>

using namespace std;

// -----------------------------------------------
// Constructor
// -----------------------------------------------
FileManagement::FileManagement()
{
}

// -----------------------------------------------
// Destructor
// -----------------------------------------------
FileManagement::~FileManagement()
{
}

/**
 * Opens a file from the file system
 * @param filePath - path to the file to be opened
 * @return string representing contents of the file
 */
string FileManagement::parseFile(string inputFileName)
{
	string outputStr;
	try 
	{
		ifstream inputFile;
		inputFile.open(inputFileName);
		if (inputFile.rdbuf()->is_open())
		{
			string line;
			while (!inputFile.eof())
			{
				getline(inputFile, line);
				//if (inputFile.eof()) continue;
				outputStr.append(line).append(" ");
			}
			inputFile.close();
		}
		else
		{
			cout << " Cannot open file " << inputFileName << endl;
			// log error
		}
	}
	catch (exception e)
	{
		// log exception
	}
	return outputStr;
}

/**
 * Writes a key:value to a text file
 * @param outputFileName - name of the file to write to
 * @param key - key
 * @param value - value
 */
void FileManagement::writeKeyValueToFile(string outputFileName, string key, int value)
{
	try 
	{
		ofstream outputFile;
		outputFile.open(outputFileName, ios::app);
		if (!outputFile.rdbuf()->is_open())
		{
			cout << " Cannot open output file" << endl;
			// log error
			return;
		}
		outputFile << "(\"" << key << "\"," << value << ")" << endl;
	} 
	catch (exception e) 
	{
		// log exception
	}
}

