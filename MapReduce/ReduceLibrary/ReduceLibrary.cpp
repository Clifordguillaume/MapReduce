// ===============================================================================
// ReduceLibrary.cpp : Defines the exported functions for the DLL.
// 
// CSE 687 MapReduce Project 2
// 
// ReduceLibrary.cpp
// 
// Author: Cliford and Elizabeth
// 
// Description: The reduce class is responsible for taking in a key and an
//				iterator of integers, summing up the values of the iterator,
//				and exporting the results to a file in the user-specified output
//				directory. 
// 
// File History:
// 5/02/22 - Cliford - Dll Initial creation
// 5/04/22 - Cliford - Dll continuation with the creation process
// 5/11/22 - Elizabeth - Modify reduceFunc to use int* data. Change getData
//						 to use string pointer arr in order to use dll extern.
//						 Add ReducedData struct and use it.
// 5/22/22 - Elizabeth - Get rid of getData and directly return reduced data from
//						 reduceFunc. Revert reduceFunc to use list<int>
// ===============================================================================
#include "pch.h"
#include <boost/algorithm/string.hpp>
#include "framework.h"
#include "FileManagement.h"
//#include <glog/logging.h>
#include "ReduceLibrary.h"

#define debug 0

// Global Variables
FileManagement* _pFileManagement = new FileManagement();

// -------------------------------------------------------------------------------
// reduceFunc
// -------------------------------------------------------------------------------
REDUCELIBRARY_API ReducedData reduceFunc(string& iKey, list<int> data)
{
	//LOG(INFO) << "Reduce.reduceFunc -- BEGIN";
	if (debug)
		cout << "Inside the reduceFunc function " << endl;

	cout << "Reducing key: " + iKey << endl;

	list<string> _lstReducedData;

	try
	{
		// Local varibales
		list<string> lstReducedData;
		string sKeyVal = iKey;
		int ikeyVal = 0;

		// get the key frequency
		for (int i : data)
		{
			ikeyVal += i;
		}

		string freq = to_string(ikeyVal);
		string finalString = "(\"" + sKeyVal + "\"," + freq + ")";

		// Add data to the global lst
		_lstReducedData.push_back(finalString);
	}
	catch (exception e)
	{
		//LOG(ERROR) << "Reduce.reduceFunc -- Exception reducing";
		//LOG(ERROR) << e.what();
	}

	int listSize = _lstReducedData.size();
	string* dataArr = new string[listSize];
	std::copy(_lstReducedData.begin(), _lstReducedData.end(), dataArr);

	ReducedData reducedData = { dataArr, listSize };

	//LOG(INFO) << "Reduce.reduceFunc -- END";

	return reducedData;
}

// -------------------------------------------------------------------------------
// export
// -------------------------------------------------------------------------------
REDUCELIBRARY_API int exportFunc(list<string> sDataToWrite, string outputFileDir)
{
	//LOG(INFO) << "Reduce.exportFunc -- BEGIN";
	if (debug)
		cout << "Inside the exportFunc function " << endl;

	// if the output dir does not end in backslash, add one and use to generate full path of temp output file
	boost::trim_right(outputFileDir);
	if (outputFileDir.back() != '\\')
	{
		outputFileDir += "\\";
	}

	// find an output file name that does not yet exist
	int i = 1;
	string fileName = outputFileDir + "FinalReducedData-0.txt";
	while (_pFileManagement->fileExists(fileName))
	{
		fileName = outputFileDir + "FinalReducedData-" + to_string(i) + ".txt";
		i++;
	}

	// remove duplicates
	sDataToWrite.unique();

	// Write info to the file
	_pFileManagement->writeToFile(fileName, sDataToWrite, true);

	//LOG(INFO) << "Reduce.exportFunc -- END";

	return 0;
}
