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
// 4/12/22 - Cliford - Added readFile() and writeToFIle()
// ===============================================================================

// Local Headers
#include "FileManagement.h"
#include <fstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>

using namespace std;

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
FileManagement::FileManagement()
{
}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
FileManagement::~FileManagement()
{
}

// -------------------------------------------------------------------------------
// parseFile
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// writeKeyValueToFile
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// readFile
// -------------------------------------------------------------------------------
list<string> FileManagement::readFile(string& iFileName)
{
	// Local variables
	list<string> oFileValue;
	string sFileName = iFileName;
	string sLine;

	// read from file and append to list
	ifstream mFile(sFileName);
	if (mFile.is_open())
	{
		while (!mFile.eof())
		{
			getline(mFile, sLine);
			// Check to prevent adding empty space at the end of the file.
			if (sLine != "") 
			{
				//cout << "File Info: " << sLine << endl;
				oFileValue.push_back(sLine);
			}
		}
		// Close the file
		mFile.close();
	}
	else 
	{	// Ran into an issue opening the file
		cout << "Problem opening the file" << endl;
	}
	return oFileValue;
}

// -------------------------------------------------------------------------------
// writeToFile
// -------------------------------------------------------------------------------
void FileManagement::writeToFile(string& sFileName, list<string> sDataToWrite)
{
	// Local Variables
	string fileName = sFileName;

	// create or open the file
	ofstream File(fileName);

	for (string lst : sDataToWrite)
	{
		// write the value to the file
		File << lst << endl;
	}

	// close the file
	File.close();
}