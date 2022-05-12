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
			virtual ~FileManagement();

			/**
			 * Checks if a file exists
			 * @param fullFilePath - full path of file including file name
			 * @return true if file exists, else false
			 */
			virtual bool fileExists(string fullFilePath);

			/**
			 * Deletes the specified file
			 * @param iFileName - full path to file that needs to be deleted
			 * @return an integer value (0) success (1) fail
			 */
			virtual int removeFile(string iFileName);

			/**
			 * Writes to a text file
			 * @param sFileName - File name to write to
			 * @param sDataToWrite - value to write to file
			 * @param iReduceFile - is set to false initially, will set to true if processing
			 *						the reduce file for more functionallity dedicated only 
									to the reduce file.
			 */
			virtual void writeToFile(string& sFileName, list<string> sDataToWrite, bool iReduceFIle = false);

		private:
	};
#endif /* FILE_MANAGEMENT_H */