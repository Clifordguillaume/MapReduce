// ===============================================================================
// CSE 687 MapReduce Project
// 
// MessageUtils.h
// 
// Author: Elizabeth and Cliford
// 
// Description: Provides utils to use for messages sent to Stub
// 
// ===============================================================================
#pragma once
#include <string>

using namespace std;

class MessageUtils
{
	public:

		/*
		 * Encode input information into a char pointer array to send to a Stub
		 * @param command - 0 for map, 1 for reduce
		 * @param inputFileDir - input file dir
		 * @param inputFileDir - 2nd input file dir
		 * @param outputFileDir - final output file dir for reduced data
		 * @param tempOutputFileDir - temporary output file dir used when mapping
		 * @param size - reference variable to hold the final size of the generated char arr
		 */
		static char* encodeMessage(int command, string inputFileDir, string outputFileDir, string tempOutputFileDir, int &size);

	private:
};
