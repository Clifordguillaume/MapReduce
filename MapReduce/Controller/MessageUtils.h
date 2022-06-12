// ===============================================================================
// CSE 687 MapReduce Project
// 
// StringUtils.h
// 
// Author: Elizabeth and Cliford
// 
// Description: Provides utils to handle strings with boost
// 
// ===============================================================================
#pragma once
#include <string>

using namespace std;

class MessageUtils
{
	public:
		static char* encodeMessage(int command, string inputFileDir, string outputFileDir, string tempOutputFileDir, int &size);

	private:
};
