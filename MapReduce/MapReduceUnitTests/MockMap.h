// ===============================================================================
// CSE 687 MapReduce Project
// 
// MockMap.h
// 
// Author: Elizabeth and Cliford
// 
// Description: Mock of Map class
//
// File History:
// 4/20/22 - Elizabeth - Initial file. Created mock methods
// 4/27/22 - Elizabeth - Add more methods
// ===============================================================================
#pragma once

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include "../MapReduce/Map.h")

#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <ObjIdl.h>

using namespace std;
using::testing::_;
using ::testing::Invoke;

namespace MapReduce
{
	class MockMap : public Map
	{
		public:
			MockMap() : Map()
			{
				// when these methods are called within other methods of the MockMap, 
				// call the actual methods in Map
				ON_CALL(*this, splitString(_)).WillByDefault(Invoke(this, &Map::splitString));
				ON_CALL(*this, removeSpecialChars(_)).WillByDefault(Invoke(this, &Map::removeSpecialChars));
				ON_CALL(*this, lowerString(_)).WillByDefault(Invoke(this, &Map::lowerString));
			}
			virtual ~MockMap() {}

			//MOCK_METHOD((std::multimap<string, int>), map, (string inputFileName, string data), (override));
			//MOCK_METHOD(string, getKey, (string str), (override));
			//MOCK_METHOD(void, exportMap, (string outputFileName, (std::multimap<string, int>) keyValMap), (override));
			//MOCK_METHOD(list<int>, getKeyValue, (string iSKey, list<string> lstOfData), (override));
			MOCK_METHOD2(map, std::multimap<string, int>(string inputFileName, string data));
			MOCK_METHOD2(exportMap, void(string outputFileName, std::multimap<string, int> keyValMap));
			MOCK_METHOD1(getKey, string(string str));
			MOCK_METHOD3(getKeyValue, list<int>(string iSKey, list<string> lstOfData, int rowsToSkip));
			MOCK_METHOD1(splitString, vector<string>(string str));
			MOCK_METHOD1(removeSpecialChars, string(string str));
			MOCK_METHOD1(lowerString, string(string str));
			MOCK_METHOD1(getQuoteIndexes, vector<int>(string str));

		private:
	};
}
