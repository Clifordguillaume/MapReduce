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
		string parseFile(string inputFileName);
		void writeKeyValueToFile(string outputFileName, string key, int value);
	private:
};
#endif /* FILE_MANAGEMENT_H */