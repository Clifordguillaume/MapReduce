// ===============================================================================
// CSE 687 MapReduce Project
// 
// FileManagement.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The FileManagement class handles interaction with the file system,
//				including reading and writing to files.
// 
// Notes:
// 
// File History:
// 5/5/22 - Elizabeth - Initial file with methods copied from MapReduce
// ===============================================================================

// Local Headers
#include "FileManagement.h"
#include <fstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <glog/logging.h>
#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <cstring>

using namespace std;

// for debugging purposes change to 0 to 
// not show cout messages in the cmd line
#define debug 0

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
// fileExists
// -------------------------------------------------------------------------------
bool FileManagement::fileExists(string fullFilePath)
{
	bool exists = true;
	try
	{
		exists = std::filesystem::exists(fullFilePath);
	}
	catch (exception e)
	{
		LOG(ERROR) << "FileManagement.fileExists -- Exception checking if file exists. File path: " + fullFilePath;
		LOG(ERROR) << e.what();
	}
	return exists;
}

// -------------------------------------------------------------------------------
// removeFile
// -------------------------------------------------------------------------------
int FileManagement::removeFile(string iFileName)
{
	//LOG(INFO) << "FileManagement.removeFile -- BEGIN";

	if (!fileExists(iFileName))
	{
		//LOG(INFO) << "FileManagement.removeFile -- File does not exist. Nothing to remove. Filename: " + iFileName;
		//LOG(INFO) << "FileManagement.removeFie -- END1";
		return 0;
	}

	//LOG(INFO) << "FileManagement.removeFile -- Removing file " + iFileName;

	// convert filename to a cstring to be able
	// to use the remove function
	const char* fileName = iFileName.c_str();
	int status = -1;

	try
	{
		status = remove(fileName);
	}
	catch (exception e)
	{
		//LOG(ERROR) << "FileManagement.removeFile -- Exception removing file " + iFileName + ":";
		//LOG(ERROR) << e.what();
	}

	//LOG(INFO) << "FileManagement.removeFie -- END";

	// return
	return status;
}

// -------------------------------------------------------------------------------
// writeKeyValueToFile
// -------------------------------------------------------------------------------
void FileManagement::writeKeyValueToFile(string outputFileName, string key, int value)
{
	//LOG(INFO) << "FileManagement.writeKeyValueToFile -- BEGIN";
	//LOG(INFO) << "FileManagement.writeKeyValueToFile -- key: " + key + ", value: " + to_string(value) + ", file: " + outputFileName;

	try
	{
		ofstream outputFile;

		// open the output file
		outputFile.open(outputFileName, ios::app);
		if (!outputFile.rdbuf()->is_open())
		{
			//LOG(ERROR) << "FileManagement.writeKeyValueToFile -- Cannot open output file " + outputFileName;
			return;
		}

		// write key-value pair to output file
		outputFile << "(\"" << key << "\"," << value << ")" << endl;

		// close the file
		outputFile.close();
	}
	catch (exception e)
	{
		//LOG(ERROR) << "FileManagement.writeKeyValueToFile -- Exception writing key-value (" + key + ", " + to_string(value) + " to file " + outputFileName;
		//LOG(ERROR) << e.what();
	}

	//LOG(INFO) << "FileManagement.writeKeyValueToFile -- END";
}