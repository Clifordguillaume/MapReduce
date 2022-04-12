// ===============================================================================
// CSE 687 MapReduce Project
// 
// FileManagement.h
// 
// Author: Elizabeth and Cliford
// 
// Description: 
// 
// Notes:
// 
// ===============================================================================
#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include <fstream>

using namespace std;

class FileManagement
{
	public:
		FileManagement();
		~FileManagement();

	/**
	 * Opens a file from the file system
	 * @param filePath - path to the file to be opened
	 * @return string representing contents of the file
	 */
		string parseFile(string inputFileName);

	/**
	 * Writes a key:value to a text file
	 * @param outputFileName - name of the file to write to
	 * @param key - key
	 * @param value - value
	 */
		void writeKeyValueToFile(string outputFileName, string key, int value);

	/**
		* Writes to a text file
		* @param sFileName - File name to write to
		* @param sValue - value to write to file
		*/
		void writeToFile(string& sFileName, string& sValue);

	private:
};
#endif /* FILE_MANAGEMENT_H */