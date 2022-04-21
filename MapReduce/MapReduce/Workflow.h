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

#include "BaseClass.h"
#include "Map.h"
#include "Reduce.h"
#include "Sorter.h"
#include <map>
#include <memory>

class Workflow : public BaseClass
{
	public:
		std::unique_ptr<Map> _pMap;
		std::unique_ptr<Reduce> _pReduce;
		std::unique_ptr<Sorter> _pSorter;

		Workflow();
		virtual ~Workflow();

		/**
		 * Run map, sort, and reduce
		 * @param inputFileDir - name of directory to read input files from
		 * @param outputFileDir - name of directory to write final output files to
		 * @param tempOutputFileDir - name of directory to write temp output files to
		 */
		void run(string inputFileDir, string outputFileDir, string tempOutputFileDir);

		/**
		 * Maps input file contents to output file
		 * @param inputFileDir - name of directory to read input files from
		 * @param outputFileName - name of output file
		 */
		void map(string inputFileDir, string outputFileName);

		/**
		 * Sorts contents of a file
		 * @param tempDirectory -directory that contains all the temp files to be sorted
		 * @return int returns 0 to comple function task
		 */
		int sort(string tempDirectory);

		/**
		 * Reduce a list of data to a single output file
		 * @param lstOfData - list of data to reduce
		 */
		void reduce(string tempDirectory);

	private:
};
#endif /* WORKFLOW_H */