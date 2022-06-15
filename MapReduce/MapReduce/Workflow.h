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

#define _HAS_STD_BYTE 0

#include "FileManagement.h"
#include "Map.h"
#include "Reduce.h"
#include "Sorter.h"
#include <map>
#include <memory>
#include <boost/function.hpp>

namespace MapReduce
{
	class Workflow
	{
		public:
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
			virtual void setupMapDLL();

			/**
			 * Set up the ReduceLibrary dll functions
			 */
			virtual void setupReduceDLL();

			/**
			 * Maps input file contents to output file
			 * @param inputFileDir - name of directory to read input files from
			 * @param outputFileDirName - name of temp output file dir
			 * @returns list of read input files
			 */
			virtual list<string> map(string inputFileDir, string outputFileDirName);

			/**
			 * Function to to feed to the thread to complete the map process
			 * @param inputFileName - name of directory to read input files from
			 * @param tempOutputFileDir - name of temp file directory to use
			 * @returns none
			 */
			virtual void mapThreadData(string inputFileName, string tempOutputFileDir);

			/**
			 * Reduces a list of data to a single output file
			 * @param lstOfData - list of data to reduce
			 * @param outputFileDir - directory to put final output file
			 */
			virtual void reduce(string tempDirectory, string outputFileDir);

			/**
			 * Reduces the contents of a file
			 * @param file - the file to reduce
			 */
			virtual void reduceFile(string file);

			/**
			 * Save data that has been reduced to a text file in a given output dir
			 * @param outputFileDir - directory to save results to
			 */
			virtual void saveReducedData(string outputFileDir);

		private:
	};
}
#endif /* WORKFLOW_H */