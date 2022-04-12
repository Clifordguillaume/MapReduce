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
// 4/9/22 - Elizabeth - Initial map, splitString, removeSpecialChars, lowerString 
//			method implementations
// 4/10/22 - Remove FileManagement references from Map
// ===============================================================================

#include "Map.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
Map::Map() 
{
}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
Map::~Map() 
{
}

// -------------------------------------------------------------------------------
// map
// -------------------------------------------------------------------------------
std::map<string, int> Map::map(string inputFileName, string data) 
{
	// tokenize the string represenation of the contents of the file
	string loweredStr = lowerString(data);
	string strippedLowerStr = removeSpecialChars(loweredStr);
	vector<string> splitStr = splitString(strippedLowerStr);

	// populate map with words and their frequencies
	std::map<string, int> wordCounts;
	for (string s : splitStr) 
	{
		if (wordCounts.count(s) < 1)
		{
			wordCounts.insert({ s, 1 });
		}
		else 
		{
			wordCounts[s] = wordCounts[s] + 1;
		}
	}

	return wordCounts;
}

// -------------------------------------------------------------------------------
// splitString
// -------------------------------------------------------------------------------
vector<string> Map::splitString(string str) 
{
	vector<string> splitStr;
	boost::trim(str);
	boost::split(splitStr, str, boost::is_any_of("\t "), boost::token_compress_on); // token_compress_on used for adjacent separators
	// TODO: Remove empty strings from vector
	return splitStr;
}

// -------------------------------------------------------------------------------
// removeSpecialChars
// -------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------
// lowerString
// -------------------------------------------------------------------------------
string Map::lowerString(string str) 
{
	boost::algorithm::to_lower(str); // use boost to_lower
	return str;
}

// -------------------------------------------------------------------------------
// getKey
// -------------------------------------------------------------------------------
string Map::getKey(string iStr)
{
	int length = 0;

	// remove the quoations around the 
	// string to find the key.
	string str = iStr;
	length = str.size();

	string str2 = str.substr(2, length);

	length = str2.size();
	string str3 = str2.substr(0, length - 3);

	// Get key and return
	string sKey = str3;
	return sKey;
}


// -------------------------------------------------------------------------------
// getKeyValue
// -------------------------------------------------------------------------------
list<int> Map::getKeyValue(string iSKey, list<string> lstOfData)
{
	list<int> iKeyValue;
	for (auto it = lstOfData.begin(); it != lstOfData.end(); ++it)
	{
		cout << "map lstOfData: " << *it << endl;

		string sFullString = *it;
		string stringToFind = iSKey;
		int pos = 0;
		int index;
		while ((index = sFullString.find(stringToFind, pos)) != string::npos) {

			// found a match
			cout << "Match found at position: " << index << endl;
			//pos = index + 1; //new position is from next element of index

			int length = 0;
			// remove the front part of the string
			string str = *it;
			string str2 = str.substr(2, length);

			length = str2.size();
			string str3 = str2.substr((length - 1), length); //("cliford", 1)

			// Get key and return
			string sKey = str3;

			int sKeyValue = stoi(sKey);
			iKeyValue.push_back(sKeyValue);
		}
	}
	return iKeyValue;
}