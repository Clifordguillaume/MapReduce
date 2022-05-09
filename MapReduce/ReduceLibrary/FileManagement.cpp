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
// 4/24/22 - Elizabeth - Added glogs, Add checks for empty file directories, add
//						 checks for text files
// 4/25/22 - Elizabeth - Add createSuccessFile()
// 4/28/22 - Elizabeth - Remove extra SUCCESS file creation
// ===============================================================================

// Local Headers
#include "pch.h"
#include "FileManagement.h"
#include <fstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
//#include <glog/logging.h>
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
	// clearDirectory
	// -------------------------------------------------------------------------------
	void FileManagement::clearDirectory(string& iDirPath)
	{
		//LOG(INFO) << "FileManagement.clearDirectory -- BEGIN";
		//LOG(INFO) << "FileManagement.clearDirectory -- Clearing directory " + iDirPath;

		if (debug)
			cout << "Entering clearDirectory()" << endl;

		// get list of all files in input file directory
		list<string> tempFiles = getTextFilesInDirectory(iDirPath);

		// Loop though and remove each file
		for (string file : tempFiles)
		{
			try
			{
				// delete the file
				int status = removeFile(file);
				if (status == 0)
				{
					if (debug)
						cout << "FileManagement.clearDirectory -- File: " << file << " was deleted successfully!" << endl;
				}
				else
				{
					if (debug)
						cout << "FileManagement.clearDirectory -- File: " << file << " (NOT) deleted successfully!" << endl;
				}
			}
			catch (exception e) 
			{
				//LOG(ERROR) << "FileManagement.clearDirectory -- Exception removing file " + file + ":";
				//LOG(ERROR) << e.what();
			}
		}

		if (debug)
			cout << "Exiting clearDirectory()" << endl;

		//LOG(INFO) << "FileManagement.clearDirectory -- END";
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
			//LOG(ERROR) << "FileManagement.fileExists -- Exception checking if file exists. File path: " + fullFilePath;
			//LOG(ERROR) << e.what();
		}
		return exists;
	}

	// -------------------------------------------------------------------------------
	// getFileName
	// -------------------------------------------------------------------------------
	string FileManagement::getFileName(string fullFilePath)
	{
		string filename;
		try 
		{
			filename = std::filesystem::path(fullFilePath).filename().stem().string();
		}
		catch (exception e)
		{
			//LOG(ERROR) << "FileManagement.getFileName -- Exception getting file name from string: " + fullFilePath;
			//LOG(ERROR) << e.what();
		}

		return filename;
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

	bool isTextFile(string fileName)
	{
		return (fileName.size() >= 3 && 0 == fileName.compare(fileName.size() - 3, 3, "txt", 3));
	}

	// -------------------------------------------------------------------------------
	// getFilesInDirectory
	// -------------------------------------------------------------------------------
	list<string> FileManagement::getTextFilesInDirectory(string fileDirName)
	{
		//LOG(INFO) << "FileManagement.getFilesInDirectory -- BEGIN";
		//LOG(INFO) << "FileManagement.getFilesInDirectory -- Getting files in directory " + fileDirName;

		list<string> filePaths;
		try {
			for (const auto& entry : std::filesystem::directory_iterator(fileDirName))
			{
				string filePath = entry.path().string();
				if (isTextFile(filePath))
				{
					filePaths.push_back(filePath);
				}			
			}
		}
		catch (exception e)
		{
			//LOG(ERROR) << "FileManagement.getFilesInDirectory -- Exception getting files in directory " + fileDirName + ":";
			//LOG(ERROR) << e.what();
		}

		if (filePaths.size() <= 0)
		{
			//LOG(INFO) << "FileManagement.getFilesInDirectory -- No text files found in directory " + fileDirName;
		}

		//LOG(INFO) << "FileManagement.getFilesInDirectory -- END";

		return filePaths;
	}

	// -------------------------------------------------------------------------------
	// readFile
	// -------------------------------------------------------------------------------
	list<string> FileManagement::readFile(string& iFileName)
	{
		//LOG(INFO) << "FileManagement.readFile -- BEGIN";
		//LOG(INFO) << "FileManagement.readFile -- Reading file " + iFileName;
		if (debug)
			cout << "reading file" << endl;

		// store contents of file in list of each line value
		list<string> oFileValue;

		try
		{
			// do not attempt to read if file is not text file
			if (!isTextFile(iFileName))
			{
				//LOG(INFO) << "FileManagement.readFile -- File is not a text file. Not reading. File: " + iFileName;
				//LOG(INFO) << "FileManagement.readFile -- END1";
				return oFileValue;
			}

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
				//LOG(ERROR) << "FileManagement.readFile -- Could not open " + iFileName;
			}
		}
		catch (exception e)
		{
			//LOG(ERROR) << "FileManagement.readFile -- Exception while reading file" + iFileName;
			//LOG(ERROR) << e.what();
		}

		//LOG(INFO) << "FileManagement.readFile -- END";

		return oFileValue;
	}

	// -------------------------------------------------------------------------------
	// writeToFile
	// -------------------------------------------------------------------------------
	void FileManagement::writeToFile(string& sFileName, list<string> sDataToWrite, bool iReduceFIle)
	{
		//LOG(INFO) << "FileManagement.writeToFile -- BEGIN";
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
						//LOG(INFO) << "FileManagement.writeToFile -- File " + sFileName + " already existed. Deleted to re-write.";
						if (debug)
							cout << "File: " << fileName << " exist and was deleted successfully!" << endl;
					}
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
			//LOG(ERROR) << "FileManagement.writeToFile -- Exception writing to file";
			//LOG(ERROR) << e.what();
		}

		//LOG(INFO) << "FileManagement.writeToFile -- END";

	}

	// -------------------------------------------------------------------------------
	// writeKeyValueToFile
	// -------------------------------------------------------------------------------
	void FileManagement::writeKeyValueToFile(string outputFileName, string key, int value)
	{
		//LOG(INFO) << "FileManagement.writeKeyValueToFile -- BEGIN";
		//LOG(INFO) << "FileManagement.writeKeyValueToFile -- key: " + key + ", value: " + to_string(value) + ", file: " + outputFileName;

		if (debug)
			cout << "inside the writeKeyValueToFile function" << endl;
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

	// -------------------------------------------------------------------------------
	// createSuccessFile
	// -------------------------------------------------------------------------------
	void FileManagement::createSuccessFile(string outputFileDir)
	{
		//LOG(INFO) << "FileManagement.createSuccessFile -- BEGIN";

		try
		{
			string successFileName;

			// make the absolute path to the SUCCESS.txt file
			boost::trim_right(outputFileDir);
			if (outputFileDir.back() != '\\')
			{
				successFileName = outputFileDir + "\\SUCCESS.txt";
			}
			else
			{
				successFileName = outputFileDir + "SUCCESS.txt";
			}

			// delete the file if it already exists
			if (fileExists(successFileName))
			{
				removeFile(successFileName);
			}

			// create the empty file
			writeToFile(successFileName, {}, false);
		}
		catch (exception e)
		{
			//LOG(ERROR) << "FileManagement.createSuccessFile -- Exception creating SUCCESS file. Exception:";
			//LOG(ERROR) << e.what();
		}

		//LOG(INFO) << "FileManagement.createSuccessFile -- END";
	}