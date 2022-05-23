// ===============================================================================
// CSE 687 MapReduce Project
// 
// KeyValUtils.h
// 
// Author: Elizabeth and Cliford
// 
// Description: The KeyValUtils provides utilities for handling key-values
//				used by the MapReduce program.
// 
// ===============================================================================

#ifndef KEYVALUTILS_H
#define KEYVALUTILS_H

// Local Headers
#include <list>
#include <string>
#include <vector>

using namespace std;

namespace MapReduce
{
	class KeyValUtils
	{
		public:

			/**
			 * Gets the key from a full string
			 * @param str - whole string to retrieve the key from
			 * @return the key found
			 */
			static std::string getKey(std::string str);

			/**
			 * Gets the value from a full string
			 * @param str - whole string to retrieve the value from
			 * @return the value found
			 */
			static std::string getValue(std::string str);

			/**
			 * Gets a list of values in a given list of data that correspond to the same given key
			 * @param iSKey - Key to find the values for
			 * @param lstOfData - list of original data
			 * @param rowsToSkip - number of entries in the lstOfData to skip over
			 * @return KeyValues struct containing the key, an array of values found corresponding to the key
			 *		   and the number of values in the values array
			 */
			static list<int> getKeyValues(std::string iSKey, list<std::string> lstOfData, int rowsToSkip);

			/**
			 * Get all indexes where a double quote character is found
			 * @input str - input string
			 * @return vector of indexes in the string where quote found
			 */
			static vector<int> getQuoteIndexes(std::string str);

		private:

	};
}
#endif /* KEYVALUTILS_H */
