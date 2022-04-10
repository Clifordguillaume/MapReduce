// ===============================================================================
// CSE 687 MapReduce Project
// 
// Map.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: 
//              
// 
// FileHistory:
// 4/9/22 - Elizabeth - Initial map, splitString, removeSpecialChars, lowerString method implementations
// ===============================================================================

#include "Map.h"
#include "FileManagement.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>

using namespace std;

// -----------------------------------------------
// Constructor
// -----------------------------------------------
Map::Map() 
{
}

// -----------------------------------------------
// Destructor
// -----------------------------------------------
Map::~Map() 
{
}

/**
 * Reads an input file and writes words and frequencies to an output file
 * @param inputFileName - name of input file
 * @param outputFileName - name of output file
 * @param data - data to write
 */
void Map::map(string inputFileName, string outputFileName, string data) 
{
	// tokenize the string represenation of the contents of the file
	string loweredStr = lowerString(data);
	string strippedLowerStr = removeSpecialChars(loweredStr);
	vector<string> splitStr = splitString(strippedLowerStr);

	// populate map with words and their frequencies
	std::map<string, int> wordCount;
	for (string s : splitStr) 
	{
		if (wordCount.count(s) < 1)
		{
			wordCount.insert({ s, 1 });
		}
		else 
		{
			wordCount[s] = wordCount[s] + 1;
		}
	}

	// write entries in map to file
	std::map<string, int>::iterator it;
	for (it = wordCount.begin(); it != wordCount.end(); it++)
	{
		string word = it->first;
		int wordFreq = it->second;
		writeKeyValueToFile(outputFileName, word, wordFreq);
	}
}

/**
 * Calls file manager to write a key value pair to a specified output file
 * @param outputFileName - name of file to write to
 * @param key - key
 * @param value - value
 */
void Map::writeKeyValueToFile(string outputFileName, string key, int value) 
{
	FileManagement fileManager;
	fileManager.writeKeyValueToFile(outputFileName, key, value);
}

/**
 * Splits a string into a vector of strings, split by whitespace
 * @input str - string to split
 * @return vector of strings that were separated by whitespace
 */
vector<string> Map::splitString(string str) 
{
	vector<string> splitStr;
	boost::trim(str);
	boost::split(splitStr, str, boost::is_any_of("\t "), boost::token_compress_on); // token_compress_on used for adjacent separators
	// TODO: Remove empty strings from vector
	return splitStr;
}

/**
 * Removes all special characters from a string
 * @param str - string to remove special characters from
 * @return string with special characters removed
 */
string Map::removeSpecialChars(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		// remove all characters that are not letters of english alphabet
		char c = str[i];
		if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && !isspace(c))
		{
			str.erase(i, 1);
			i--;
		}
	}
	return str;
}

/**
 * Converts a string to all lowercase letters
 * @input istr - input string
 * @return str with all characters coverted to lowercase letters
 */
string Map::lowerString(string str) 
{
	boost::algorithm::to_lower(str); // use boost to_lower
	return str;
}