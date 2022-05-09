// ===============================================================================
// CSE 687 MapReduce Project
// 
// FileManagement.h
// 
// Author: Elizabeth
// 
// Description: The FileManagement class handles interaction with the file system,
//				including reading and writing to files.
// 
// ===============================================================================
#pragma once
#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include <fstream>
#include <list>
#include <string>

using namespace std;

class FileManagement
{
	public:
		FileManagement();
		virtual ~FileManagement();

		/**
		 * Checks if a file exists
		 * @param fullFilePath - full path of file including file name
		 * @return true if file exists, else false
		 */
		bool fileExists(string fullFilePath);

		/**
		 * Deletes the specified file
		 * @param iFileName - full path to file that needs to be deleted
		 * @return an integer value (0) success (1) fail
		 */
		int removeFile(string iFileName);

		/**
		 * Writes a key and its value to a text file
		 * @param outputFileName - name of the file to write to
		 * @param key - key
		 * @param value - value
		 */
		void writeKeyValueToFile(string outputFileName, string key, int value);

	private:
};
#endif /* FILE_MANAGEMENT_H */