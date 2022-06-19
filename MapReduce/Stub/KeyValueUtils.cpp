// ===============================================================================
// CSE 687 MapReduce Project
// 
// KeyValUtils.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The KeyValUtils provides utilities for handling key-values
//				used by the MapReduce program.
// 
// FileHistory:
// 6/10/22 - Copy from MapReduce project to Stub
// ===============================================================================

// Local Headers
#include "KeyValUtils.h"
#include <list>
#include <string>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;

namespace Stub
{
	// -------------------------------------------------------------------------------
	// getKey
	// -------------------------------------------------------------------------------
	std::string KeyValUtils::getKey(std::string iStr)
	{
		// ONLY UNCOMMENT IF DEBUGGING
		//LOG(INFO) << "Map.getKey -- BEGIN";
		//LOG(INFO) << "Map.getKey -- Getting key from string " + iStr;

		std::string key;
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
	// getValue
	// -------------------------------------------------------------------------------
	std::string KeyValUtils::getValue(std::string str)
	{
		// find index of the comma 
		int commaIndx = str.find(',');

		// find index of closing parenthesis
		int closingParenthesisIndx = str.find(')');

		// extract the string between the comma and the closing parentheis
		std::string valueStr = str.substr(commaIndx + 1, closingParenthesisIndx - 2);

		// trim the string
		boost::trim(valueStr);

		return valueStr;
	}

	// -------------------------------------------------------------------------------
	// getKeyValues
	// -------------------------------------------------------------------------------
	list<int> KeyValUtils::getKeyValues(std::string iSKey, list<std::string> lstOfData, int rowsToSkip)
	{
		//LOG(INFO) << "Map.getKeyValue -- BEGIN"; // ONLY UNCOMMENT IF DEBUGGING

		list<int> keyValList;
		list<std::string> trimmedListOfData;
		list<std::string>::iterator it = lstOfData.begin();
		advance(it, rowsToSkip);
		trimmedListOfData.splice(trimmedListOfData.end(), lstOfData, it, lstOfData.end());

		try
		{
			for (std::string dataEntry : trimmedListOfData)
			{
				// get the key value of the current row of data
				std::string key = getKey(dataEntry);

				// if the key of the current row of data matches key to find values for
				if (key == iSKey)
				{
					std::string valueStr = getValue(dataEntry);
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

		return keyValList;
	}

	// -------------------------------------------------------------------------------
	// getQuoteIndexes
	// -------------------------------------------------------------------------------
	vector<int> KeyValUtils::getQuoteIndexes(std::string str)
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

}
