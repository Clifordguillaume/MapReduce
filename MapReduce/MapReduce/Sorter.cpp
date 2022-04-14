// ===============================================================================
// CSE 687 MapReduce Project
// 
// Sorter.cpp
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
// 04/12/22 Cliford - created the SortingClass and added the sort ()
// ===============================================================================

// Local Headers
#include "Sorter.h"
#include "Map.h"
#include "FileManagement.h"

#include <algorithm>

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
Sorter::Sorter() {}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
Sorter::~Sorter() {}

// -------------------------------------------------------------------------------
// Sort
// -------------------------------------------------------------------------------
list<string> Sorter::sort(string& iFilePath)
{
	// Local Variables
	string FileName = iFilePath;
	list<string> lstFileValue;

	FileManagement ManageFile;
	lstFileValue = ManageFile.readFile(FileName);

	// Sort the data in the list
	lstFileValue.sort();

	// preview what's in the file
	//for (string lst : lstFileValue) 
	//{
	//	cout << lst << endl;
	//}
	return lstFileValue;
}