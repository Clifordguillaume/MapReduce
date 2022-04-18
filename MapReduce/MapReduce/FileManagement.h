// ===============================================================================
// CSE 687 MapReduce Project
// 
// FileManagement.h
// 
// Author: Elizabeth and Cliford
// 
// Description: The FileManagement class handles interaction with the file system,
//				including reading and writing to files.
// ===============================================================================
#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include <fstream>
#include <list>

using namespace std;

class FileManagement
{
	public:
		FileManagement();
		~FileManagement();

		/**
		 * Checks if a file exists
		 * @param fullFilePath - full path of file including file name
		 * @return true if file exists, else false
		 */
		bool fileExists(string fullFilePath);

		/**
		 * Gets the name of the file without full path or file extension
		 * @param fullFilePath - full path of the file including file name
		 * @return name of file
		 */
		string getFileName(string fullFilePath);

		/**
		 * Traverses a given directory and returns list of files it contains
		 * @param fileDirName - Name of the directory to traverse
		 * @return list of the paths to all files in the directory
		 */
		list<string> getFilesInDirectory(string fileDirName);
		
		/**
		 * Reads data from the file
		 * @param sFileName - File name to read from
		 * @preturn the list containing the file data
		 */
		list<string> readFile(string& iFileName);

		/**
		 * Writes to a text file
		 * @param sFileName - File name to write to
		 * @param sDataToWrite - value to write to file
		 */
		void writeToFile(string& sFileName, list<string> sDataToWrite);

		/**
		 * Writes a key:value to a text file
		 * @param outputFileName - name of the file to write to
		 * @param key - key
		 * @param value - value
		 */
		void writeKeyValueToFile(string outputFileName, string key, int value);

	private:
};
#endif /* FILE_MANAGEMENT_H */