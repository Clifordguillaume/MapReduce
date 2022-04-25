// ===============================================================================
// CSE 687 MapReduce Project
// 
// Map.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: Provides utilities to read an input file's contents and store its
//				words in a map that can be exported to another file.
//              
// 
// FileHistory:
// 4/9/22 - Elizabeth - Initial map, splitString, removeSpecialChars, lowerString 
//						method implementations
// 4/10/22 - Elizabeth - Remove FileManagement references from Map
// 4/12/22 - Cliford - Added getkey() and getkeyValue()
// 4/13/22 - Elizabeth - Clean up string parsing methods. Add exportMap()
// 4/14/22 - Elizabeth - Change map() and exportMap() to use multimap to allow 
//						 duplicate keys (words) with each having frequency = 1
// 4/19/22 - Elizabeth - Change FileManagement to pointer
// 4/20/22 - Elizabeth - Add filemanagementpointer, namespace
// 4/24/22 - Elizabeth - Add glogs, add delete file before export
// ===============================================================================

#include "Map.h"
#include <glog/logging.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

// for debugging purposes change to 0 to 
// not show cout messages in the cmd line
#define debug 0

namespace MapReduce 
{
	// -------------------------------------------------------------------------------
	// Constructor
	// -------------------------------------------------------------------------------
	Map::Map()
	{
		_pFileManagement = new FileManagement();
	}

	// -------------------------------------------------------------------------------
	// Destructor
	// -------------------------------------------------------------------------------
	Map::~Map()
	{
		delete _pFileManagement;
		LOG(INFO) << "Map component destroyed";
	}

	// -------------------------------------------------------------------------------
	// map
	// -------------------------------------------------------------------------------
	std::multimap<string, int> Map::map(string inputFileName, string data)
	{
		LOG(INFO) << "Map.map -- BEGIN";
		LOG(INFO) << "Map.map -- Received string: " + data + " ...from input file " + inputFileName;

		if (debug)
			cout << "Inside the map function " << endl;

		std::multimap<string, int> wordCounts;
		try {
			// tokenize the string represenation of the contents of the file
			string loweredStr = lowerString(data);
			string strippedLowerStr = removeSpecialChars(loweredStr);
			vector<string> splitStr = splitString(strippedLowerStr);

			// populate map with words and their frequencies
			for (string s : splitStr)
			{
				wordCounts.insert({ s, 1 });
			}
		}
		catch (exception e)
		{
			LOG(ERROR) << "Map.map -- Exception mapping data from input file " + inputFileName;
			LOG(ERROR) << e.what();
		}

		LOG(INFO) << "Map.map -- END";

		return wordCounts;
	}

	// -------------------------------------------------------------------------------
	// exportMap
	// -------------------------------------------------------------------------------
	void Map::exportMap(string outputFileName, std::multimap<string, int> keyValMap)
	{
		LOG(INFO) << "Map.exportMap -- BEGIN";
		if (debug)
			cout << "Inside the exportMap function " << endl;

		// delete output file if it already exists (removeFile already checks)
		_pFileManagement->removeFile(outputFileName);

		// write entries in map to file
		std::map<string, int>::iterator it;
		for (it = keyValMap.begin(); it != keyValMap.end(); it++)
		{
			try 
			{
				// get key and value
				string key = it->first;
				int value = it->second;

				// write key and value to file
				_pFileManagement->writeKeyValueToFile(outputFileName, key, value);
			}
			catch (exception e)
			{
				LOG(ERROR) << "Map.exportMap -- Exception exporting map to output file " + outputFileName;
				LOG(ERROR) << e.what();
			}
		}

		LOG(INFO) << "Map.exportMap -- END";
	}

	// -------------------------------------------------------------------------------
	// splitString
	// -------------------------------------------------------------------------------
	vector<string> Map::splitString(string str)
	{
		LOG(INFO) << "Map.splitString -- BEGIN";
		LOG(INFO) << "Map.splitString -- Splitting string";
		if (debug)
			cout << "Inside the splitString function " << endl;

		vector<string> splitStr;

		try {
			// remove whitespace from string start and end
			boost::trim(str);

			// split the string based on tabs and spaces
			boost::split(splitStr, str, boost::is_any_of("\t "), boost::token_compress_on); // token_compress_on used for adjacent separators
		}
		catch (exception e)
		{
			LOG(ERROR) << "Map.splitString -- Exception splitting string " + str;
			LOG(ERROR) << e.what();
		}
		
		LOG(INFO) << "Map.splitString -- END";

		return splitStr;
	}

	// -------------------------------------------------------------------------------
	// removeSpecialChars
	// -------------------------------------------------------------------------------
	string Map::removeSpecialChars(string str)
	{
		LOG(INFO) << "Map.removeSpecialChars -- BEGIN";
		LOG(INFO) << "Map.removeSpecialChars -- Removing special chars from string";
		string result;
		try 
		{
			for (int i = 0; i < str.length(); i++)
			{
				// remove all characters that are not letters of english alphabet or spaces
				char c = str[i];
				if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || isspace(c))
				{
					result.push_back(c);
				}
			}
		}
		catch (exception e)
		{
			LOG(ERROR) << "Map.removeSpecialChars -- Exception removing special characters from string " + str;
			LOG(ERROR) << e.what();
		}
		LOG(INFO) << "Map.removeSpecialChars -- Removed special chars from string";
		return result;
	}

	// -------------------------------------------------------------------------------
	// removeSpecialChars
	// -------------------------------------------------------------------------------
	vector<int> Map::getQuoteIndexes(string str)
	{
		vector<int> indexes;
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == '\"');
				indexes.push_back(i);
		}
		return indexes;
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
		LOG(INFO) << "Map.getKey -- BEGIN";
		LOG(INFO) << "Map.getKey -- Getting key from string " + iStr;
		if (debug)
			cout << "Inside the getKey function " << endl;

		string key;
		try {
			int length = 0;

			// remove the quoations around the 
			// string to find the key.
			string str = iStr;
			length = str.size();

			string str2 = str.substr(2, length);

			length = str2.size();
			string str3 = str2.substr(0, length - 4);

			// Get key and return
			key = str3;
		}
		catch (exception e)
		{
			LOG(ERROR) << "Map.getKey -- Exception getting key from string " + iStr;
		}
		
		LOG(INFO) << "Map.getKey -- Key " + key + " extracted";
		LOG(INFO) << "Map.getKey -- END";

		return key;
	}


	// -------------------------------------------------------------------------------
	// getKeyValue
	// -------------------------------------------------------------------------------
	list<int> Map::getKeyValue(string iSKey, list<string> lstOfData)
	{
		LOG(INFO) << "Map.getKeyValue -- BEGIN";
		if (debug)
			cout << "Inside the getKeyValue function " << endl;

		list<int> iKeyValue;
		try
		{
			for (string lst : lstOfData)
			{
				//cout << "map lstOfData: " << lst << endl;

				string sFullString = lst;
				string stringToFind = iSKey;
				int pos = 0;
				int index;
				while (index = sFullString.find(stringToFind, pos) != string::npos) {

					// found a match
					//cout << "Match found at position: " << index << endl;
					//pos = index + 1; //new position is from next element of index

					int length = 0;
					// remove the front part of the string
					string str = lst;
					length = str.size();
					string str2 = str.substr(2, length);

					length = str2.size();
					string str3 = str2.substr((length - 2), 1); //("cliford", 1)

					// Get key and return
					string sKey = str3;

					int sKeyValue = stoi(sKey);
					iKeyValue.push_back(sKeyValue);
					break;
				}
			}
		}
		catch (exception e)
		{
			LOG(ERROR) <<  "Map.getKeyValue -- Exception getting value of key: " + iSKey;
			LOG(ERROR) << e.what();
		}

		return iKeyValue;
	}
}