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
// 04/12/22 - Cliford - created the SortingClass and added the sort ()
// 4/20/22 - Elizabeth - Add filemanagement pointer, Constructor, Destructor
// 4/24/22 - Elizabeth - Add glogs
// ===============================================================================

// Local Headers
#include "Sorter.h"
#include "FileManagement.h"
#include <glog/logging.h>

#include <algorithm>

// for debugging purposes change to 0 to 
// not show cout messages in the cmd line
#define debug 0

namespace MapReduce
{
	// -------------------------------------------------------------------------------
	// Constructor
	// -------------------------------------------------------------------------------
	Sorter::Sorter()
	{
		_pFileManagement = new FileManagement();
	}

	// -------------------------------------------------------------------------------
	// Destructor
	// -------------------------------------------------------------------------------
	Sorter::~Sorter()
	{
		delete _pFileManagement;
		LOG(INFO) << "Sorter component destroyed";
	}

	// -------------------------------------------------------------------------------
	// Sort
	// -------------------------------------------------------------------------------
	int Sorter::sort(string& iFilePath)
	{
		LOG(INFO) << "Sorter.sort -- BEGIN";
		if (debug)
			cout << "Inside the sort function from the sorted class " << endl;

		LOG(INFO) << "Sorter.sort -- Sorting contents of file " + iFilePath;

		// Local Variables
		string FileName = iFilePath;
		list<string> lstFileValue;

		lstFileValue = _pFileManagement->readFile(FileName);

		// Sort the data in the list
		lstFileValue.sort();

		// write the sorted data to the file
		FileManagement fileManager;
		fileManager.writeToFile(FileName, lstFileValue);

		// preview what's in the file
		//for (string lst : lstFileValue) 
		//{
		//	cout << lst << endl;
		//}

		LOG(INFO) << "Sorter.sort -- END";

		// return
		return 0;
	}
}