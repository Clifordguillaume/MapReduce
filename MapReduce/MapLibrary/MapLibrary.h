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
	// Number of words in the SplitWords words array
	int wordCount;

	// Array of words
	string* words;

	/**
	 */
	SplitWords(int count, string* w)
	{
		wordCount = count;
		words = w;
	}
};
/**
 * Reads an input file and writes words and frequencies to an output file
 * @param inputFileName - name of input file
 * @param data - data to tokenize
 * @return map of words and counts
*/
extern "C" MAPLIBRARY_API WordCount* map(string inputFileName, string data);

/**
 * Writes a map of words and counts to a specified output file
 * @param outputFileName - name of file to write to
 * @param wordCounts - array of WordCounts holding words and their counts
 */
extern "C" MAPLIBRARY_API void exportMap(string outputFileName, WordCount* wordCounts);

/**
 * Gets the key from a full string
 * @param str - whole string to retrieve the key from
 * @return the key found
 */
extern "C" MAPLIBRARY_API string getKey(string str);

/**
 * Gets a list of values in a given list of data that correspond to the
 * same given key
 * @param iSKey - Key to find the values for
 * @param lstOfData - list of original data
 * @param rowsToSkip - number of entries in the lstOfData to skip over
 * @return array containing values found corresponding to the key
 */
extern "C" MAPLIBRARY_API int* getKeyValue(string iSKey, list<string> lstOfData, int rowsToSkip);

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

/**
 * Get all indexes where a double quote character is found
 * @input str - input string
 * @return vector of indexes in the string where quote found
 */
MAPLIBRARY_API vector<int> getQuoteIndexes(string str);