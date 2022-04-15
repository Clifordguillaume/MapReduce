// ===============================================================================
// CSE 687 MapReduce Project
// 
// Workflow.h
// 
// Author: Elizabeth and Cliford
// 
// Description: The Workflow handles the mapping, sorting, and reducing of data
//              received from the user from the Executive.
// ===============================================================================
#ifndef WORKFLOW_H
#define WORKFLOW_H

#include "FileManagement.h"
#include "Map.h"
#include <map>

class Workflow
{
	public:
		Workflow();
		~Workflow();

		/**
		 * Run map, sort, and reduce
		 * @param inputFileDir - name of directory to read input files from
		 * @param outputFileDir - name of directory to write final output files to
		 * @param tempOutputFileDir - name of directory to write temp output files to
		 */
		void run(string inputFileDir, string outputFileDir, string tempOutputFileDir);

	private:
		// variables
		FileManagement fileManager;
		Map mapper;

		/**
		 * Maps input file contents to output file
		 * @param inputFileDir - name of directory to read input files from
		 * @param outputFileName - name of output file
		 */
		void map(string inputFileDir, string outputFileName);

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
#endif /* WORKFLOW_H */