// ===============================================================================
// CSE 687 MapReduce Project
// 
// Executive.h
// 
// Author: Elizabeth and Cliford
// 
// Description: This Executive class handles all primary steps in the Map-Reduce 
//				program based on user input via command line.
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
		// variables
		FileManagement fileManager;
		Map mapper;

		/**
		 * Maps input file contents to output file
		 * @param inputFileName - name of input file
		 * @param outputFileName - name of output file
		 */
		void map(string inputFileName, string outputFileName);

		/**
		 * Sorts contents of a file
		 * @param fileName - name of file whose contents is to be sorted
		 * @return list of sorted items
		 */
		list<string> sort(string fileName);

		/**
		 * Reduce a list of data to a single output file
		 * @param lstOfData - list of data to reduce
		 */
		void reduce(list<string> lstOfData);
};
#endif /* EXECUTIVE_H */