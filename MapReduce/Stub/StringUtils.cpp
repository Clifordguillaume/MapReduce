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
// 6/9/22 - Elizabeth - Initial file with trim_whitespace() and parseMessage()
// ===============================================================================
#include "StringUtils.h"
#include <vector>
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;

// -------------------------------------------------------------------------------
// trim_whitespace
// -------------------------------------------------------------------------------
string StringUtils::trim_whitespace(string str)
{
	string s = str;
	boost::trim_left(s);
	boost::trim_right(s);
	return s;
}

// -------------------------------------------------------------------------------
// parseMessage
// -------------------------------------------------------------------------------
vector<string> StringUtils::parseMessage(string message)
{
    std::stringstream ss(message);

    vector<string> result;

    while (ss.good())
    {
        string substr;
        getline(ss, substr, ';');
        boost::trim_left(substr); // trim whitespace
        boost::trim_right(substr); // trim whitespace
        result.push_back(substr);
    }

    return result;
}