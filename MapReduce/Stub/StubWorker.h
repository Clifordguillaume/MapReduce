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
#pragma once
#include <string>
#include <vector>
#include <winsock2.h>
#include "../MapReduce/Workflow.h")

using namespace std;
using namespace MapReduce;

class StubWorker
{
	public:
		// Pointer to Workflow to handle mapping/reducing
		Workflow* _pWorkflow = new Workflow();

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

	private:
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
