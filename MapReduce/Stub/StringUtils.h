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
#include <vector>

using namespace std;

class StringUtils
{
	public:
		/*
		 * Trims whitespace from beginning and end of string
		 * @param str - string to trim
		 */
		static string trim_whitespace(string str);

		/*
		 * Split a message separated by semi-colons into strings
		 * @param message - message to split
		 * @return vector of split strings
		 */
		static vector<string> parseMessage(string message);

	private:
};