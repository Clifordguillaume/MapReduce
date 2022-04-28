// ===============================================================================
// CSE 687 MapReduce Project
// 
// MockReduce.h
// 
// Author: Elizabeth and Cliford
// 
// Description: Mock of Reduce class
//	
// File History:
// 4/20/22 - Elizabeth - Initial mock methods
// ===============================================================================
#pragma once

#include "gmock/gmock.h"  // Brings in gMock.
#include "../MapReduce/Reduce.h")

using namespace std;

namespace MapReduce
{
	class MockReduce : public Reduce
	{
		public:
			MOCK_METHOD2(reduceFunc, int(string& iKey, list<int> iLstOfData));
			MOCK_METHOD1(exportFunc, int(list<string> sDataToWrite));
			MOCK_METHOD(list<string>, GetData, (), (override));
		
		private:
	};
}