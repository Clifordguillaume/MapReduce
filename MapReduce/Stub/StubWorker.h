// ===============================================================================
// CSE 687 MapReduce Project
// 
// StubWorker.h
// 
// Author: Elizabeth and Cliford
// 
// Description: The StubWorker handles the map and reduce done by the Stub
// 
// ===============================================================================
#ifndef STUB_WORKER_H
#define STUB_WORKER_H

#include "Sorter.h"
#include "FileManagement.h"
#include <string>

using namespace std;

namespace Stub
{
	class StubWorker
	{
		public:
			StubWorker();
			~StubWorker();

			/*
			 * Handle a message from the controller
			 * @param msg - the message to handle
			 */
			void handleMessage(string msg);

			/*
			 * Mark the job as done
			 */
			void markDone();

			/*
			 * Check if the stub job (map or reduce) has completed yet
			 */
			bool isDoneExecuting();

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
				* @param callback function from StubWorker
				* @param StubWorker pointer needed for callback
				* @returns list of read input files
				*/
			virtual list<string> map(string inputFileDir, string outputFileDirName, boost::function<void(StubWorker*)>, StubWorker* me);

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
			Sorter* _pSorter;
			FileManagement* _pFileManagement;

			// Flag indicating if stub job (map or reduce) has completed yet
			volatile bool done;

			// The command that was received from the controller
			string command;

			// input file directory
			string inputFileDir;

			// ouput file directory
			string outputFileDir;

			// temp output file directory
			string tempOutputFileDir;
	};
}
#endif /* STUB_WORKER_H */
