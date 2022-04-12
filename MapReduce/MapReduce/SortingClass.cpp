// ===============================================================================
// CSE 687 MapReduce Project
// 
// SortingClass.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The intermediary results will need to be sorted and aggregated. 
//				The intermediate file will contain output such as: (“a”, 1), 
//				(“the”, 1), (“is”, 1), (“the”, 1), (“a”, 1). The reducer requires 
//				the same data in the format: (“a, [1, 1, …]), (“the”, [1, 1, …]), 
//				(“is”, [1, …]), …
//
// File History:
// ===============================================================================

// Local Headers
#include "SortingClass.h"
#include "Map.h"
#include "FileManagement.h"

#include <algorithm>

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
SortingClass::SortingClass() {}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
SortingClass::~SortingClass() {}

// -------------------------------------------------------------------------------
// Sort
// -------------------------------------------------------------------------------
int SortingClass::Sort(string& iFilePath)
{
	// Local Variables
	string FileName = iFilePath;
	string FileData = "";

	FileManagement ManageFile;

	FileData = ManageFile.parseFile(FileName);

	// the file data
	Sort(FileData.begin(), FileData.end());
}