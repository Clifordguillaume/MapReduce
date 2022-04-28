// ===============================================================================
// CSE 687 MapReduce Project
// 
// MockSorter.h
// 
// Author: Elizabeth and Cliford
// 
// Description: Mock of Sorter class
//	
// File History:
// 4/20/22 - Elizabeth - Initial file. Created mock methods
// ===============================================================================
#pragma once

#include "gmock/gmock.h"  // Brings in gMock.
#include "../MapReduce/Sorter.h")

using namespace std;

namespace MapReduce
{
	class MockSorter : public Sorter
	{
		public:
			MOCK_METHOD1(sort, int(string& iFilePath));

		private:
	};
}