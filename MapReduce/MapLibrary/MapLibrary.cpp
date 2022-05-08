// ===============================================================================
// CSE 687 MapReduce Project
// 
// MapLibrary.cpp
// 
// Author: Elizabeth
// 
// Description: Provides utilities to read an input file's contents and store its
//				words in a map that can be exported to another file.
//              
// 
// FileHistory:
// 5/4/22 - Elizabeth - Initial file creation with methods copied from MapReduce
// 5/4/22 - Elizabeth - Remove std dependencies from methods
// 5/6/22 - Elizabeth - Continue removing std dependencies
// ===============================================================================
#pragma once
#include "FileManagement.h"
#include "MapLibrary.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// -------------------------------------------------------------------------------
// map
// -------------------------------------------------------------------------------
MAPLIBRARY_API WordCount* mapFunc(string inputFileName, string data, int* _pNumWords)
{
	//LOG(INFO) << "Map.map -- BEGIN";
	//LOG(INFO) << "Map.map -- Received string: " + data + " ...from input file " + inputFileName;

	try {

		// initialize num words pointer if null
		if (_pNumWords == NULL) 
		{
			_pNumWords = new int();
		}

		// tokenize the string represenation of the contents of the file
		string loweredStr = lowerString(data);
		string strippedLowerStr = removeSpecialChars(loweredStr);
		SplitWords splitWords = splitString(strippedLowerStr);
	
		// get the number of words and the array of words
		int numWords = splitWords.wordCount;
		string* words = splitWords.words;
		*_pNumWords = numWords;

		// populate an array of WordCounts containing each word and freq = 1
		WordCount* wordCounts = new WordCount[numWords];
		for (int i = 0; i < numWords; i++)
		{
			wordCounts[i] = WordCount(words[i], 1);
		}

		return wordCounts;
	}
	catch (exception e)
	{
		//LOG(ERROR) << "Map.map -- Exception mapping data from input file " + inputFileName;
		//LOG(ERROR) << e.what();
	}

	//LOG(INFO) << "Map.map -- END";

	return {};
}

// -------------------------------------------------------------------------------
// exportMap
// -------------------------------------------------------------------------------
MAPLIBRARY_API void exportMap(string outputFileName, WordCount* wordCounts, int numWords)
{
	//LOG(INFO) << "Map.exportMap -- BEGIN";

	// delete output file if it already exists (removeFile already checks)
	FileManagement fileManagement;
	fileManagement.removeFile(outputFileName);

	// write entries in map to file
	for (int i = 0; i < numWords; i++)
	{
		try
		{
			WordCount wc = wordCounts[i];

			// get key and value
			string word = wc.word;
			int count = wc.count;

			//cout << "Map exporting word: " + word << endl;

			// write key and value to file
			fileManagement.writeKeyValueToFile(outputFileName, word, count);
		}
		catch (exception e)
		{
			//LOG(ERROR) << "Map.exportMap -- Exception exporting map to output file " + outputFileName;
			//LOG(ERROR) << e.what();
		}
	}

	//LOG(INFO) << "Map.exportMap -- END";
}

// -------------------------------------------------------------------------------
// splitString
// -------------------------------------------------------------------------------
MAPLIBRARY_API SplitWords splitString(string str)
{
	//LOG(INFO) << "Map.splitString -- BEGIN";
	//LOG(INFO) << "Map.splitString -- Splitting string";
		
	vector<string> splitStrVector;

	try {
		// remove whitespace from string start and end
		boost::trim(str);

		// split the string based on tabs and spaces
		boost::split(splitStrVector, str, boost::is_any_of("\t "), boost::token_compress_on); // token_compress_on used for adjacent separators
	}
	catch (exception e)
	{
		//LOG(ERROR) << "Map.splitString -- Exception splitting string " + str;
		//LOG(ERROR) << e.what();
	}

	int numWords = splitStrVector.size();
	string* splitStrArr = new string[numWords];
	std::copy(splitStrVector.begin(), splitStrVector.end(), splitStrArr);
	SplitWords splitWords = { numWords, splitStrArr };

	return splitWords;
}

// -------------------------------------------------------------------------------
// removeSpecialChars
// -------------------------------------------------------------------------------
MAPLIBRARY_API string removeSpecialChars(string str)
{
	//LOG(INFO) << "Map.removeSpecialChars -- BEGIN";
	//LOG(INFO) << "Map.removeSpecialChars -- Removing special chars from string";
	string result;
	int strSize = str.length();
	try
	{
		for (unsigned int i = 0; i < strSize; i++)
		{
			// remove all characters that are not letters of english alphabet or spaces
			unsigned char c = str[i];
			if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || isspace(c))
			{
				result.push_back(c);
			}
			/*if (i % 1000 == 0) {
				cout << "Reading characters " << i << "/" << strSize << endl;
			}*/
		}
	}
	catch (exception e)
	{
		//LOG(ERROR) << "Map.removeSpecialChars -- Exception removing special characters from string " + str;
		//LOG(ERROR) << e.what();
	}
	//LOG(INFO) << "Map.removeSpecialChars -- Removed special chars from string";
	return result;
}

// -------------------------------------------------------------------------------
// removeSpecialChars
// -------------------------------------------------------------------------------
MAPLIBRARY_API vector<int> getQuoteIndexes(string str)
{
	vector<int> indexes;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '\"')
		{
			indexes.push_back(i);
		}
	}
	return indexes;
}

// -------------------------------------------------------------------------------
// lowerString
// -------------------------------------------------------------------------------
MAPLIBRARY_API string lowerString(string str)
{
	boost::algorithm::to_lower(str); // use boost to_lower
	return str;
}

// -------------------------------------------------------------------------------
// getKey
// -------------------------------------------------------------------------------
MAPLIBRARY_API string getKey(string iStr)
{
	// ONLY UNCOMMENT IF DEBUGGING
	//LOG(INFO) << "Map.getKey -- BEGIN";
	//LOG(INFO) << "Map.getKey -- Getting key from string " + iStr;

	string key;
	try {
		vector<int> quoteIndexes = getQuoteIndexes(iStr);
		int firstQuoteIndx = quoteIndexes.front();
		int lastQuoteIndx = quoteIndexes.back();
		int firstCharIndx = firstQuoteIndx + 1;
		int lastCharIndx = lastQuoteIndx - 1;

		// if key is only one letter long..
		if (firstCharIndx == lastCharIndx)
		{
			key = iStr[firstCharIndx];
		}
		else // otherwise extract the key
		{
			key = iStr.substr(firstCharIndx, lastCharIndx - 1);
		}
	}
	catch (exception e)
	{
		//LOG(ERROR) << "Map.getKey -- Exception getting key from string " + iStr;
	}

	// ONLY UNCOMMENT IF DEBUGGING
	//LOG(INFO) << "Map.getKey -- Key " + key + " extracted from string " + iStr;
	//LOG(INFO) << "Map.getKey -- END";

	return key;
}


// -------------------------------------------------------------------------------
// getKeyValue
// -------------------------------------------------------------------------------
MAPLIBRARY_API int* getKeyValue(string iSKey, list<string> lstOfData, int rowsToSkip)
{
	//LOG(INFO) << "Map.getKeyValue -- BEGIN"; // ONLY UNCOMMENT IF DEBUGGING

	list<int> keyValList;
	list<string> trimmedListOfData;
	list<string>::iterator it = lstOfData.begin();
	advance(it, rowsToSkip);
	trimmedListOfData.splice(trimmedListOfData.end(), lstOfData, it, lstOfData.end());

	try
	{
		for (string dataEntry : trimmedListOfData)
		{
			// get the key value of the current row of data
			string key = getKey(dataEntry);

			// if the key of the current row of data matches key to find values for
			if (key == iSKey)
			{
				// find index of the comma 
				int commaIndx = dataEntry.find(',');

				// find index of closing parenthesis
				int closingParenthesisIndx = dataEntry.find(')');

				// extract the string between the comma and the closing parentheis
				string valueStr = dataEntry.substr(commaIndx + 1, closingParenthesisIndx - 2);

				// trim the string
				boost::trim(valueStr);

				int sKeyValue = stoi(valueStr);
				keyValList.push_back(sKeyValue);
			}
		}
	}
	catch (exception e)
	{
		//LOG(ERROR) << "Map.getKeyValue -- Exception getting value of key: " + iSKey;
		//LOG(ERROR) << e.what();
	}

	// ONLY UNCOMMENT IF DEBUGGING
	//LOG(INFO) << "Map.getKeyValue -- Extracted key value of size " + to_string(iKeyValue.size()) + " for key: " + iSKey;
	//LOG(INFO) << "Map.getKeyValue -- END";

	int listSize = keyValList.size();
	int* keyValArr = new int[listSize];
	std::copy(keyValList.begin(), keyValList.end(), keyValArr);

	return keyValArr;
}