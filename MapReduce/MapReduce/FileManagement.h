// ===============================================================================
// CSE 687 MapReduce Project
// 
// FileManagement.h
// 
// Author: Elizabeth and Cliford
// 
// Description: The FileManagement class handles interaction with the file system,
//				including reading and writing to files.
// 
// Notes:
// 
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