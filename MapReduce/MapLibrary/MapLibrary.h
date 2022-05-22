// ===============================================================================
// CSE 687 MapReduce Project
// 
// MapLibrary.h
// 
// Author: Elizabeth
// 
// Description: Provides utilities to read an input file's contents and store its
//				words in a map that can be exported to another file.
//			
// ===============================================================================

#pragma once
#include <vector>
using namespace std;

#ifdef MAPLIBRARY_EXPORTS
#define MAPLIBRARY_API __declspec(dllexport)
#else
#define MAPLIBRARY_API __declspec(dllimport)
#endif

/**
 * struct for holding a word and its count 
 */
struct WordCount {
	// A word
	string word;

	// Count associated with the word
	int count;

	/**
	 * Empty Constructor
	 */
	WordCount() 
	{
		// empty constructor
	}

	/**
	 * Constructor
	 * @param w - a word
	 * @param c - count of the word
	 */
	WordCount(string w, int c)
	{
		word = w;
		count = c;
	}
};

/**
 * struct for holding words and how many of them there are
 */
struct SplitWords {
	// Array of words
	string* words;

	// Number of words in the SplitWords words array
	int wordCount;

	/**
	 * Constructor
	 * @param w - array of words
	 * @param count - number of words in the words arr
	 */
	SplitWords(string* w, int count)
	{
		
		words = w;
		wordCount = count;
	}
};

/**
 * struct for holding a key and its combined values
 */
struct KeyValues {
	// the key associated with the values
	string key;

	// array of values
	int* valsArr;

	// the number of values in the valsArr
	int numVals = 0;

	/**
	 * Constructor
	 * @param k - the key
	 * @param vals - array of int values
	 * @param n - number of values in the vals arr
	 */
	KeyValues(string k, int* vals, int n)
	{
		key = k;
		valsArr = vals;
		numVals = n;
	}
};

/**
 * Reads an input file and writes words and frequencies to an output file
 * @param inputFileName - name of input file
 * @param data - data to tokenize
 * @param _pNumWords - number of words in map
 * @return map of words and counts
*/
extern "C" MAPLIBRARY_API WordCount* mapFunc(string inputFileName, string data, int* _pNumWords);

/**
 * Writes a map of words and counts to a specified output file
 * @param outputFileName - name of file to write to
 * @param wordCounts - array of WordCounts holding words and their counts
 * @param numWords - number of words in map
 */
extern "C" MAPLIBRARY_API void exportMap(string outputFileName, WordCount* wordCounts, int numWords);

/**
 * Splits a string into a vector of strings, split by whitespace
 * @input str - string to split
 * @return SplitWords containing array of words and count of how many
 *		   words are in the array
 */
MAPLIBRARY_API SplitWords splitString(string str);

/**
* Removes all special characters from a string
* @param str - string to remove special characters from
* @return string with special characters removed
*/
MAPLIBRARY_API string removeSpecialChars(string str);

/**
 * Converts a string to all lowercase letters
 * @input istr - input string
 * @return string with all characters coverted to lowercase letters
 */
MAPLIBRARY_API string lowerString(string str);