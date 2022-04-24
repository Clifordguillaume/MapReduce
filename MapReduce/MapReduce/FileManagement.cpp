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
// 4/8/22 - Elizabeth - Added parseFile(), writeKeyValueToFile()
// 4/9/22 - Elizabeth - Change format of output file strings
// 4/12/22 - Cliford - Added readFile() and writeToFIle()
// 4/13/22 - Elizabeth - Combine parseFile() and readFile() into single readFile()
// 4/14/22 - Elizabeth - Added getFilesInDirectory(), fileExists(), getFileName(). 
//						 Added exception logging.
// 4/20/22 - Elizabeth - Add namespace
// 4/21/22 - Cliford - Added clearDirectory()
// 4/24/22 - Cliford - Update the writeTofile() to take a third parameter for when
//					   writing the reduce data to add a few more capability
// ===============================================================================

// Local Headers
#include "FileManagement.h"
#include <fstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <cstring>

using namespace std;

// for debugging purposes change to 0 to 
// not show cout messages in the cmd line
#define debug 0

namespace MapReduce
{
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
	// clearDirectory
	// -------------------------------------------------------------------------------
	void FileManagement::clearDirectory(string& iDirPath)
	{
		if (debug)
			cout << "Entering clearDirectory()" << endl;

		// get list of all files in input file directory
		list<string> tempFiles = getFilesInDirectory(iDirPath);

		// Loop though and remove each file
		for (string file : tempFiles)
		{
			// delete the file
			int status = removeFile(file);
			if (status == 0) 
			{
				if (debug)
					cout << "File: " << file << " was deleted successfully!" << endl;
			}
			else 
			{
				if (debug)
					cout << "File: " << file << " (NOT) deleted successfully!" << endl;
			}
		}

		if (debug)
			cout << "Exiting clearDirectory()" << endl;
	}

	// -------------------------------------------------------------------------------
	// fileExists
	// -------------------------------------------------------------------------------
	bool FileManagement::fileExists(string fullFilePath)
	{
		return std::filesystem::exists(fullFilePath);
	}

	// -------------------------------------------------------------------------------
	// getFileName
	// -------------------------------------------------------------------------------
	string FileManagement::getFileName(string fullFilePath)
	{
		return std::filesystem::path(fullFilePath).filename().stem().string();
	}

	// -------------------------------------------------------------------------------
	// removeFile
	// -------------------------------------------------------------------------------
	int FileManagement::removeFile(string iFileName)
	{
		// convert filename to a cstring to be able
		// to use the remove function
		const char* fileName = iFileName.c_str();
		int status = remove(fileName);
		
		// return
		return status;
	}

	// -------------------------------------------------------------------------------
	// getFilesInDirectory
	// -------------------------------------------------------------------------------
	list<string> FileManagement::getFilesInDirectory(string fileDirName)
	{
		list<string> filePaths;
		try {
			for (const auto& entry : std::filesystem::directory_iterator(fileDirName))
			{
				string filePath = entry.path().string();
				filePaths.push_back(filePath);
			}
		}
		catch (exception e)
		{
			cout << "FileManagement.getFilesInDirectory -- Exception getting files in dir: " + fileDirName << endl;
			cout << e.what() << endl;
		}

		return filePaths;
	}

	// -------------------------------------------------------------------------------
	// readFile
	// -------------------------------------------------------------------------------
	list<string> FileManagement::readFile(string& iFileName)
	{
		if (debug)
			cout << "reading file" << endl;

		// store contents of file in list of each line value
		list<string> oFileValue;

		try
		{
			// Local variables
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
				cout << "FileManagement.readFile -- Could not open " + iFileName << endl;
			}
		}
		catch (exception e)
		{
			cout << "FileManagement.readFile -- Exception while reading file:" + iFileName << endl;
			cout << e.what() << endl;
		}

		return oFileValue;
	}

	// -------------------------------------------------------------------------------
	// writeToFile
	// -------------------------------------------------------------------------------
	void FileManagement::writeToFile(string& sFileName, list<string> sDataToWrite, bool iReduceFIle)
	{
		if (debug)
			cout << "writing to file " << endl;

		try {
			// Local Variables
			string fileName = sFileName;

			// only process this if processing the reduce file
			if (iReduceFIle)
			{
				// Check to see if the file exist if so remove it
				// that way we won't have data added to what's already there
				// instead we can start brand new.
				bool exist = fileExists(fileName);
				if (exist)
				{
					// delete the file if it's exist
					int status = removeFile(fileName);
					if (status == 0)
					{
						if (debug)
							cout << "File: " << fileName << " exist and was deleted successfully!" << endl;
					}
				}

				// create empty SUCCESS text file if not already exist
				string sSuccessfile = "SUCCESS.txt";
				exist = fileExists(sSuccessfile);
				if (!exist) 
				{
					ofstream successFile(sSuccessfile);

					// for debugging purposes
					if (debug)
						cout << "SUCCESS file was created" << endl;

					// close the file
					successFile.close();
				}
			}

			// create or write to existing file
			ofstream File(fileName);

			for (string lst : sDataToWrite)
			{
				// write the value to the file
				File << lst << endl;
			}

			// close the file
			File.close();
		}
		catch (exception e)
		{
			cout << "FileManagement.writeToFile -- Exception writing to file:" << endl;
			cout << e.what() << endl;
		}

	}

	// -------------------------------------------------------------------------------
	// writeKeyValueToFile
	// -------------------------------------------------------------------------------
	void FileManagement::writeKeyValueToFile(string outputFileName, string key, int value)
	{
		if (debug)
			cout << "inside the writeKeyValueToFile function" << endl;
		try
		{
			ofstream outputFile;

			// open the output file
			outputFile.open(outputFileName, ios::app);
			if (!outputFile.rdbuf()->is_open())
			{
				cout << " Cannot open output file" << endl;
				return;
			}

			// write key-value pair to output file
			outputFile << "(\"" << key << "\"," << value << ")" << endl;

			// close the file
			outputFile.close();
		}
		catch (exception e)
		{
			cout << "FileManagement.writeKeyValueToFile -- Exception writing key-value to file:" << endl;
			cout << e.what() << endl;
		}
	}
}