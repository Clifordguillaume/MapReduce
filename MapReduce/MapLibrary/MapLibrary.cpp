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
// 5/11/22 - Elizabeth - Change getKeyVals to return KeyVals struct object
// 5/22/22 - Elizabeth - Remove getKey, getKeyVals
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

			cout << "Map exporting word: " + word << endl;

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
	SplitWords splitWords = { splitStrArr, numWords };

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
// lowerString
// -------------------------------------------------------------------------------
MAPLIBRARY_API string lowerString(string str)
{
	boost::algorithm::to_lower(str); // use boost to_lower
	return str;
}