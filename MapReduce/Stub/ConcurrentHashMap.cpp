// ===============================================================================
// CSE 687 MapReduce Project
// 
// ConcurrentHashMap.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: This wraps functions of a hash map into a thread safe 
//				data structure.
//              
// 
// File History:
// 6/10/22 - Copy from MapReduce project to Stub
// ===============================================================================

// unique_lock example
#include "ConcurrentHashMap.h"
#include "ReduceLibrary.h"
#include "KeyValUtils.h"
#include <mutex>
#include <map>

using namespace std;

namespace Stub
{
	// mutex
	static std::mutex mtx;

	// map
	static map<string, int> dataMap;

	// -------------------------------------------------------------------------------
	// addToMap
	// -------------------------------------------------------------------------------
	void ConcurrentHashMap::addToMap(ReducedData reducedData)
	{
		std::unique_lock<std::mutex> lck(mtx);
		string* data = reducedData.reducedData;
		int numDataRows = reducedData.numRows;

		for (int i = 0; i < numDataRows; i++)
		{
			string dataStr = data[i];
			string key = KeyValUtils::getKey(dataStr);
			string strVal = KeyValUtils::getValue(dataStr);
			int intVal = stoi(strVal);

			// check if map already contains key
			std::map<string, int>::iterator it = dataMap.find(key);
			if (it != dataMap.end())
			{
				// if key already exists, add value to it
				it->second += intVal;
			}
			else // otherwise add new entry to map
			{
				dataMap.insert({ key, intVal });
			}
		}
	}

	// -------------------------------------------------------------------------------
	// getMapContents
	// -------------------------------------------------------------------------------
	list<string> ConcurrentHashMap::getMapContents()
	{
		std::unique_lock<std::mutex> lck(mtx);

		list<string> mapContents;

		// loop through the entire map
		for (auto const& [key, val] : dataMap)
		{
			// construct key-val pair string
			string keyValStr = "(\"" + key + "\"," + to_string(val) + ")";

			// Add data to the lst
			mapContents.push_back(keyValStr);
		}

		return mapContents;
	}
}
