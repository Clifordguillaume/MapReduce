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
// 5/9/22 - Cliford - Initial file
// 5/11/22 - Elizabeth - Remove unused methods
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