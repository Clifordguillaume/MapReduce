// ===============================================================================
// CSE 687 MapReduce Project
// 
// Map.h
// 
// Author: Elizabeth and Cliford
// 
// Description: Provides utilities to read an input file's contents and store its
//				words in a map that can be exported to another file.
//			
// ===============================================================================
#ifndef MAP_H
#define MAP_H

#include "FileManagement.h"

#include <fstream>
#include <vector>
#include <map>
#include <list>

using namespace std;

namespace MapReduce 
{
	class Map
	{
		public:
			FileManagement* _pFileManagement;

			Map();
			Map(FileManagement* _pFM) : _pFileManagement(_pFM) {}
			virtual ~Map();

			/**
			 * Reads an input file and writes words and frequencies to an output file
			 * @param inputFileName - name of input file
			 * @param data - data to tokenize
			 * @return map of words and counts
			 */
			virtual std::multimap<string, int> map(string inputFileName, string data);

			/**
			 * Writes a map of words and counts to a specified output file
			 * @param outputFileName - name of file to write to
			 * @param keyValMap - map containing data to write to the file
			 */
			virtual void exportMap(string outputFileName, std::multimap<string, int> keyValMap);

			/**
			 * Gets the key from a full string
			 * @param str - whole string to retrieve the key from
			 * @return the key found
			 */
			virtual string getKey(string str);

			/**
			 * Gets a list of values in a given list of data that correspond to the
			 * same given key
			 * @param iSKey - Key to find the values for
			 * @param lstOfData - list of original data
			 * @param rowsToSkip - number of entries in the lstOfData to skip over
			 * @return list of values found corresponding to the key
			 */
			virtual list<int> getKeyValue(string iSKey, list<string> lstOfData, int rowsToSkip);

			/**
			 * Splits a string into a vector of strings, split by whitespace
			 * @input str - string to split
			 * @return vector of strings that were separated by whitespace
			 */
			virtual vector<string> splitString(string str);

			/**
			 * Removes all special characters from a string
			 * @param str - string to remove special characters from
			 * @return string with special characters removed
			 */
			virtual string removeSpecialChars(string str);

			/**
			 * Converts a string to all lowercase letters
			 * @input istr - input string
			 * @return string with all characters coverted to lowercase letters
			 */
			virtual string lowerString(string str);

			/**
			 * Get all indexes where a double quote character is found
			 * @input str - input string
			 * @return vector of indexes in the string where quote found
			 */
			virtual vector<int> getQuoteIndexes(string str);

		private:
			
	};
}
#endif /* MAP_H */