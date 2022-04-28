// ===============================================================================
// CSE 687 MapReduce Project
// 
// MockFileManagement.h
// 
// Author: Elizabeth and Cliford
// 
// Description: Mock of FileManagement class
//
// File History:
// 4/20/22 - Elizabeth - Initial file. Created mock methods
// 4/27/22 - Elizabeth - Add more methods
// ===============================================================================
#pragma once

#include "gmock/gmock.h"  // Brings in gMock.
#include "../MapReduce/FileManagement.h")

using namespace std;

namespace MapReduce
{
	class MockFileManagement : public FileManagement
	{
		public:
			MOCK_METHOD1(clearDirectory, void(string& iDirPath));
			MOCK_METHOD1(fileExists, bool(string fullFilePath));
			MOCK_METHOD1(getFileName, string(string fullFilePath));
			MOCK_METHOD1(removeFile, int(string iFileName));
			MOCK_METHOD1(getTextFilesInDirectory, list<string>(string fileDirName));
			MOCK_METHOD1(readFile, list<string>(string& iFileName));
			MOCK_METHOD2(writeToFile, void(string& sFileName, list<string> sDataToWrite));
			MOCK_METHOD3(writeKeyValueToFile, void(string outputFileName, string key, int value));
			MOCK_METHOD1(createSuccessFile, void(string outputFileDir));
		
		private:
	};
}