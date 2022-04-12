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
// 04/12/22 Cliford - created the SortingClass and added the sort function
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
list<string> SortingClass::Sort(string& iFilePath)
{
	// Local Variables
	string FileName = iFilePath;
	string FileData = "";
	list<string> lstFileValue;

	FileManagement ManageFile;
	lstFileValue = ManageFile.readFile(FileName);

	// Sort the data in the list
	lstFileValue.sort();

	// preview what's in the file
	for (auto it = lstFileValue.begin(); it != lstFileValue.end(); it++) 
	{
		cout << *it << endl;
	}
	return lstFileValue;
}