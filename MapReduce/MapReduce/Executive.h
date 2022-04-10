// ===============================================================================
// CSE 687 MapReduce Project
// 
// Executive.h
// 
// Author: Elizabeth and Cliford
// 
// Description: 
//              
// 
// Notes:
// 
// ===============================================================================
#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "FileManagement.h"
#include "Map.h"
#include <map>

using namespace std;

class Executive
{
	public:
		Executive();
		~Executive();
		void run(string inputFileName, string outputFileName);

	private:
		FileManagement fileManager;
		Map map;
		void writeMapOutput(string outputFileName, std::map<string, int> mapToWrite);
};
#endif /* EXECUTIVE_H */