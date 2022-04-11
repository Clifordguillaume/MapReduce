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

	 /**
	 * Run
	 * @input inputFileName - name of input file to read from
	 * @input outputFileName - name of file to write results to
	 */
		void run(string inputFileName, string outputFileName);

	private:

	/**
	 * Writes a map contents to a specified file
	 * @param outputFileName - name of file to write to
	 * @param mapToWrite - the map of data to write
	 */
		void writeMapOutput(string outputFileName, std::map<string, int> mapToWrite);


		FileManagement fileManager;
		Map map;
};
#endif /* EXECUTIVE_H */