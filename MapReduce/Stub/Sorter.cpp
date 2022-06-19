// ===============================================================================
// CSE 687 MapReduce Project
// 
// Sorter.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The Sorter class is responsible for taking in inputs containing
//				keys and one value per key, and sorting it in alphabetical order.
//
// File History:
// 6/13/22 - Copy from MapReduce to Stub
// ===============================================================================

// Local Headers
#include "Sorter.h"
#include "FileManagement.h"
#include <glog/logging.h>

namespace Stub
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
		//LOG(INFO) << "Sorter.sort -- BEGIN";

		//LOG(INFO) << "Sorter.sort -- Sorting contents of file " + iFilePath;

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

		//LOG(INFO) << "Sorter.sort -- END";

		// return
		return 0;
	}
}
