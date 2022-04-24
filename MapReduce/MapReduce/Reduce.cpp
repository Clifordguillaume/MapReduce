// ===============================================================================
// CSE 687 MapReduce Project
// 
// Reduce.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The reduce class will have a method that will take a string with 
//				one key and an iterator of integers. The reduce function should 
//				sum all the values in the iterator and then call an export() 
//				function (different from the Map class). The export function will 
//				take two parameters, the key and resulting reduced value, and 
//				write the result out to the output directory. Upon success an 
//				additional empty file SUCCESS will be written out to the output 
//				directory. The reduce method itself should not directly deal 
//				with any File IO. 
// 
// File History:
// 4/10/22 - Cliford - Added reduceFunc(), exportFunc()
// 4/12/22 - Cliford - Added GetData()
// 4/20/22 - Elizabeth - Add filemanagement pointer, namespace
// 4/24/22 - Elizabeth - Add glogs
// ===============================================================================

// Local Headers
#include "Reduce.h"
#include <glog/logging.h>

// STL Heades 
#include <list>
#include <iostream>
#include <string>

// for debugging purposes change to 0 to 
// not show cout messages in the cmd line
#define debug 0

namespace MapReduce
{
	// -------------------------------------------------------------------------------
	// Constructor
	// -------------------------------------------------------------------------------
	Reduce::Reduce()
	{
		_pFileManagement = new FileManagement();
	}

	// -------------------------------------------------------------------------------
	// Destructor
	// -------------------------------------------------------------------------------
	Reduce::~Reduce()
	{
		delete _pFileManagement;
		LOG(INFO) << "Reduce component destroyed";
	}

// -------------------------------------------------------------------------------
// reduceFunc
// -------------------------------------------------------------------------------
int Reduce::reduceFunc(string& iKey, list<int> oLstOfData)
{
	LOG(INFO) << "Reduce.reduceFunc -- BEGIN";
	if (debug)
		cout << "Inside the reduceFunc function " << endl;

	try 
	{
		// Local varibales
		list<string> lstReducedData;
		string sKeyVal = iKey;
		int ikeyVal = 0;

		// get the key frequency
		list<int>::iterator itr;
		for (int lst : oLstOfData)
		{
			ikeyVal = ikeyVal + 1;
		}

		string str1 = "(\"";
		string s1 = "\",";
		string str2 = str1 + sKeyVal + s1;
		string s = to_string(ikeyVal);
		string finalString = str2 + s + ")";

		// Add data to the global lst
		_lstReducedData.push_back(finalString);

	}
	catch (exception e)
	{
		LOG(ERROR) << "Reduce.reduceFunc -- Exception reducing";
		LOG(ERROR) << e.what();
	}

	LOG(INFO) << "Reduce.reduceFunc -- END";

	return 0;
}

	// -------------------------------------------------------------------------------
	// export
	// -------------------------------------------------------------------------------
	int Reduce::exportFunc(list<string> sDataToWrite)
	{
		LOG(INFO) << "Reduce.exportFunc -- BEGIN";
		if (debug)
			cout << "Inside the exportFunc function " << endl;

		// Write info to the file
		string fileName = "FinalReducedData.txt";

		// remove duplicates
		sDataToWrite.unique();
		_pFileManagement->writeToFile(fileName, sDataToWrite, true);

		LOG(INFO) << "Reduce.exportFunc -- END";

		return 0;
	}

	// -------------------------------------------------------------------------------
	// GetData
	// -------------------------------------------------------------------------------
	list<string>  Reduce::GetData()
	{
		return _lstReducedData;
	}
}