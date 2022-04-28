// ===============================================================================
// CSE 687 MapReduce Project
// 
// test.cc
// 
// Author: Elizabeth and Cliford
// 
// Description: Test suite for MapReduce project
//
// File History:
// 4/20/22 - Elizabeth - Initial file
// 4/27/22 - Elizabeth - Add tests
// ===============================================================================
#include "MockMap.h"
#include "MockFileManagement.h"
#include "MockReduce.h"
#include "MockSorter.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include "../MapReduce/Workflow.h")

using namespace std;
using namespace MapReduce;

/*
// Test the map functionality
TEST(MapTests, TestMapFuncInWorkflow)
{
	// set vars to use in test
	string testInputDir = "testinputdir";
	string testTempOutDir = "testtempoutdir";
	list<string> testInputFiles = { "test1.txt" };
	list<string> testFileContents = { "test1" };
	string firstInputFile = testInputFiles.front();
	string firstFileContents = testFileContents.front();
	std::multimap<string, int> testMap;

	// create mock objects
	MockMap mockMap;
	MockReduce mockReduce;
	MockSorter mockSorter;
	MockFileManagement mockFM;

	// create Workflow object with mocks
	Workflow w(&mockFM, &mockMap, &mockSorter, &mockReduce);

	// mock returns of functions
	EXPECT_CALL(mockFM, getTextFilesInDirectory(testInputDir)).WillOnce(testing::Return(testInputFiles))
	EXPECT_CALL(mockFM, readFile(firstInputFile)).WillOnce(testing::Return(firstFileContents))
	EXPECT_CALL(mockMap, map(firstInputFile, firstFileContents)).WillOnce(testing::Return(testMap))
	EXPECT_CALL(mockFM, getFileName(firstInputFile)).WillOnce(testing::Return("test1"));

	// set expects of how many times functions should be called
	EXPECT_CALL(mockFM, getTextFilesInDirectory(testInputDir)).Times(1);
	EXPECT_CALL(mockFM, readFile(firstInputFile)).Times(1);
	EXPECT_CALL(mockMap, map(firstInputFile, firstFileContents)).Times(1);
	EXPECT_CALL(mockFM, getFileName(firstInputFile)).Times(1);
	EXPECT_CALL(mockMap, exportMap("test1-tempOutput.txt", testMap));

	// call the map method
	w.map(testInputDir, "testtempoutputdir");
}

// Test the Sort Functionality
TEST(SorterTests, TestSortFuncInWorkflow)
{
	// set vars to use in test
	string testTempOutDir = "testtempoutdir";
	list<string> testTempOutputFiles = { "test1-output.txt" };

	// create mock objects
	MockMap mockMap;
	MockReduce mockReduce;
	MockSorter mockSorter;
	MockFileManagement mockFM;

	// create Workflow object with mocks
	Workflow w(&mockFM, &mockMap, &mockSorter, &mockReduce);

	// mock returns of functions
	EXPECT_CALL(mockFM, getTextFilesInDirectory(testTempOutDir)).WillOnce(testing::Return(testTempOutputFiles));

	// set expects of how many times functions should be called
	EXPECT_CALL(mockFM, getTextFilesInDirectory(testTempOutDir)).Times(1);
	EXPECT_CALL(mockSorter, sort("test1-output.txt")).Times(1);

	// call the sort method
	w.sort(testTempOutDir);
}

// Test the reduce functionality
TEST(ReducerTests, TestReduceFuncInWorkflow)
{
	// set vars to use in test
	string testTempOutDir = "testtempoutdir";
	string testOutputDir = "testoutdir";
	list<string> testTempOutputFiles = { "test1-output.txt" };
	list<string> testFileContents = { "test1" };
	string firstTempOutputFile = testTempOutputFiles.front();
	string firstFileContents = testFileContents.front();

	// create mock objects
	MockMap mockMap;
	MockReduce mockReduce;
	MockSorter mockSorter;
	MockFileManagement mockFM;

	// create Workflow object with mocks
	Workflow w(&mockFM, &mockMap, &mockSorter, &mockReduce);

	// mock returns of functions
	EXPECT_CALL(mockFM, getTextFilesInDirectory(testTempOutputDir)).WillOnce(testing::Return(testTempOutputFiles));
	EXPECT_CALL(mockFM, readFile(firstTempOutputFile)).WillOnce(testing::Return(firstFileContents));

	// set expects
	EXPECT_CALL(mockFM, getTextFilesInDirectory(testTempOutputDir)).Times(1);
	EXPECT_CALL(mockFM, readFile(firstTempOutputFile)).Times(1);
	EXPECT_CALL(mockMap, getKey(firstFileContents)).Times(1); // times 1 because only 1 entry in filedata
	EXPECT_CALL(mockMap, getKeyValue(AnyString(), AnyObject(), AnyInt())).Times(1); // times 1 because only 1 entry in filedata
	EXPECT_CALL(mockReduce, reduceFunc(AnyString(), AnyObject())).Times(1); // times 1 because only 1 entry in filedata
	EXPECT_CALL(mockReduce, GetData()).Times(1);
	EXPECT_CALL(mockFM, createSuccessFile(testOutputDir)).Times(1);

	// call the reduce method
	w.reduce(testTempOutDir, testOutputDir);
}
*/