// ===============================================================================
// CSE 687 MapReduce Project
// 
// Map.h
// 
// Author: Elizabeth and Cliford
// 
// Description: 
//              
// 
// Notes:
// 
// ===============================================================================
#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <vector>
#include <map>
#include <list>

using namespace std;

class Map
{
	public:
		Map();
		~Map();

	 /**
	 * Reads an input file and writes words and frequencies to an output file
	 * @param inputFileName - name of input file
	 * @param data - data to tokenize
	 * @return map of words and counts
	 */
		std::map<string, int> map(string inputFileName, string data);

		string getKey(string str);
		list<int> getKeyValue(string iSKey, list<string> lstOfData);

	private:
	/**
	 * Splits a string into a vector of strings, split by whitespace
	 * @input str - string to split
	 * @return vector of strings that were separated by whitespace
	 */
		vector<string> splitString(string str);

	 /**
	 * Removes all special characters from a string
	 * @param str - string to remove special characters from
	 * @return string with special characters removed
	 */
		string removeSpecialChars(string str);

	/**
	 * Converts a string to all lowercase letters
	 * @input istr - input string
	 * @return str with all characters coverted to lowercase letters
	 */
		string lowerString(string str);
};
#endif /* MAP_H */