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
// ===============================================================================
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
		~FileManagement();

		/**
		* Remove all files from a given directory
		* @param iDirPath - full path of of directory
		*/
		static void clearDirectory(string& iDirPath);

		/**
		 * Checks if a file exists
		 * @param fullFilePath - full path of file including file name
		 * @return true if file exists, else false
		 */
		static bool fileExists(string fullFilePath);

		/**
		 * Gets the name of the file without full path or file extension
		 * @param fullFilePath - full path of the file including file name
		 * @return name of file
		 */
		static string getFileName(string fullFilePath);

		/**
		 * Deletes the specified file
		 * @param iFileName - full path to file that needs to be deleted
		 * @return an integer value (0) success (1) fail
		 */
		static int removeFile(string iFileName);

		/**
		 * Traverses a given directory and returns list of text files it contains
		 * @param fileDirName - Name of the directory to traverse
		 * @return list of the paths to all text files in the directory
		 */
		static list<string> getTextFilesInDirectory(string fileDirName);

		/**
		 * Reads data from the file
		 * @param iFileName - full path of file to read from
		 * @return the list containing the file data
		 */
		static list<string> readFile(string& iFileName);

		/**
		 * Writes to a text file
		 * @param sFileName - File name to write to
		 * @param sDataToWrite - value to write to file
		 * @param iReduceFile - is set to false initially, will set to true if processing
		 *						the reduce file for more functionallity dedicated only
								to the reduce file.
		 */
		static void writeToFile(string& sFileName, list<string> sDataToWrite, bool iReduceFIle = false);

		/**
		 * Writes a key and its value to a text file
		 * @param outputFileName - name of the file to write to
		 * @param key - key
		 * @param value - value
		 */
		static void writeKeyValueToFile(string outputFileName, string key, int value);

		/**
		 * Creates an empty SUCCESS.txt file in the given output file dir
		 * @param outputFileDir - name of directory to write SUCCESS file to
		 */
		static void createSuccessFile(string outputFileDir);

	private:
};
#endif /* FILE_MANAGEMENT_H */