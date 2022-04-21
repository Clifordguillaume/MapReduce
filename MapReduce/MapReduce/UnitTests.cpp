// ===============================================================================
// CSE 687 MapReduce Project
// 
// UnitTests.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: Unit Tests
//              
// 
// File History:
// 4/19/22 - Elizabeth - 
// ===============================================================================

#define BOOST_TEST_MODULE My_Tests
#define BOOST_AUTO_TEST_MAIN
#define BOOST_ALL_DYN_LINK

// Local Headers
#include <boost/test/unit_test.hpp>
#include <turtle/mock.hpp>
#include "BaseClass.h"
#include "Sorter.h"
#include "Map.h"
#include "FileManagement.h"
#include "Reduce.h"
#include "Workflow.h"
#include "Executive.h"

// Turtle Documenation: 
// http://turtle.sourceforge.net/turtle/reference.html#turtle.reference.creation
// 
// SYNTAX NOTES:
// MOCK_BASE_CLASS(nameOfMockClass, ClassToMock)
// MOCK_METHOD(originalMethodName, numArgs)

// -------------------------------------------------------------------------------
// Mock FileManagement class
// -------------------------------------------------------------------------------
MOCK_BASE_CLASS(MockFileManagement, FileManagement)
{

    MOCK_METHOD(fileExists, 1);
    MOCK_METHOD(getFileName, 1);
    MOCK_METHOD(getFilesInDirectory, 1);
    MOCK_METHOD(readFile, 1);
    MOCK_METHOD(writeToFile, 2);
    MOCK_METHOD(writeKeyValueToFile, 3);
};

// -------------------------------------------------------------------------------
// Mock Map class
// -------------------------------------------------------------------------------
MOCK_BASE_CLASS(MockMap, Map)
{
    MOCK_METHOD(map, 2);
    MOCK_METHOD(exportMap, 2);
    MOCK_METHOD(getKey, 1);
    MOCK_METHOD(getKeyValue, 2);
    // cannot mock private methods splitString(), removeSpecialChars(), lowerString()
};

// -------------------------------------------------------------------------------
// Mock Sorter class
// -------------------------------------------------------------------------------
MOCK_BASE_CLASS(MockSorter, Sorter)
{
    MOCK_METHOD(sort, 1);
};

// -------------------------------------------------------------------------------
// Mock Reduce class
// -------------------------------------------------------------------------------
MOCK_BASE_CLASS(MockReduce, Reduce)
{
    MOCK_METHOD(reduceFunc, 2);
    MOCK_METHOD(exportFunc, 1);
    MOCK_METHOD(GetData, 0);
};

// -------------------------------------------------------------------------------
// Mock Workflow Class
// -------------------------------------------------------------------------------
MOCK_BASE_CLASS(MockWorkflow, Workflow)
{
    MOCK_METHOD(run, 3);
    MOCK_METHOD(map, 2);
    MOCK_METHOD(sort, 1);
    MOCK_METHOD(reduce, 1);
};

BOOST_AUTO_TEST_CASE(test_map)
{
    MockMap mockMap;
    std::unique_ptr<MockMap> _pMockMap = std::make_unique<MockMap>(mockMap);
    std::unique_ptr<MockFileManagement> _pMockFileManagement = std::make_unique<MockFileManagement>();
    mockMap._pFileManagement = std::move(_pMockFileManagement);
    Workflow w;
    w._pMap = std::move(_pMockMap);

    w.map("C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\TestInputFileDir", "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\TestOutputFileDir");

    //MOCK_EXPECT(mockMap.map).exactly(1);

}