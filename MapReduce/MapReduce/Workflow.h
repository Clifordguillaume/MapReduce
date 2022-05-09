// ===============================================================================
// CSE 687 MapReduce Project
// 
// Workflow.h
// 
// Author: Elizabeth and Cliford
// 
// Description: The Workflow handles the mapping, sorting, and reducing of data
//              received from the user from the Executive.
// 
// ===============================================================================
#ifndef WORKFLOW_H
#define WORKFLOW_H

#include "FileManagement.h"
#include "Map.h"
#include "Reduce.h"
#include "Sorter.h"
#include <map>
#include <memory>

namespace MapReduce
{
	class Workflow
	{
		public:
			Map* _pMap;
			Reduce* _pReduce;
			Sorter* _pSorter;
			FileManagement* _pFileManagement;

			Workflow();
			Workflow(FileManagement* _pFM, Map* _pM, Sorter* _pS, Reduce* _pR);
			virtual ~Workflow();

			/**
			 * Runs map, sort, and reduce
			 * @param inputFileDir - name of directory to read input files from
			 * @param outputFileDir - name of directory to write final output files to
			 * @param tempOutputFileDir - name of directory to write temp output files to
			 */
			virtual void run(string inputFileDir, string outputFileDir, string tempOutputFileDir);

			/**
			 * Set up the MapLibrary dll functions
			 */
			virtual void setupReduceDLL();

			/**
			 * Maps input file contents to output file
			 * @param inputFileDir - name of directory to read input files from
			 * @param outputFileName - name of output file
			 * @returns list of read input files
			 */
			virtual list<string> map(string inputFileDir, string outputFileName);

			/**
			 * Sorts contents of a file
			 * @param tempDirectory -directory that contains all the temp files to be sorted
			 * @return int returns 0 to comple function task
			 */
			virtual int sort(string tempDirectory);

			/**
			 * Reduces a list of data to a single output file
			 * @param lstOfData - list of data to reduce
			 * @param outputFileDir - directory to put final output file
			 */
			virtual void reduce(string tempDirectory, string outputFileDir);

		private:
	};
}
#endif /* WORKFLOW_H */