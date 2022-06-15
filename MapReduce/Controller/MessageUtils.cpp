// ===============================================================================
// CSE 687 MapReduce Project
// 
// StringUtils.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: Provides utils to handle strings with boost
// 
// File History:
// 6/11/13 - Elizabeth - Initial file with encodeMessage()
// ===============================================================================
#include "MessageUtils.h"

using namespace std;

// -------------------------------------------------------------------------------
// encodeMessage
// -------------------------------------------------------------------------------
char* MessageUtils::encodeMessage(int command, string inputFileDir, string outputFileDir, string tempOutputFileDir, int &size)
{
    // +4 for semicolons
    size = 4 + sizeof(int) + inputFileDir.size() + outputFileDir.size() + tempOutputFileDir.size();
    char* msg = new char[size];
    snprintf(msg, size, "%4d;%s;%s;%s;", command, inputFileDir.c_str(), outputFileDir.c_str(), tempOutputFileDir.c_str());

    return msg;
}