// ===============================================================================
// ReduceLibrary.cpp : Defines the exported functions for the DLL.
// 
// CSE 687 MapReduce Project 2
// 
// ReduceLibrary.cpp
// 
// Author: Cliford
// 
// Description: The reduce class is responsible for taking in a key and an
//				iterator of integers, summing up the values of the iterator,
//				and exporting the results to a file in the user-specified output
//				directory. 
// 
// File History:
// 5/02/22 - Cliford - Dll Initial creation
// 5/04/22 - Cliford - Dll continuation with the creation process
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
list<string> _lstReducedData;


// -------------------------------------------------------------------------------
// reduceFunc
// -------------------------------------------------------------------------------
REDUCELIBRARY_API int reduceFunc(string& iKey, list<int> oLstOfData)
{
	//LOG(INFO) << "Reduce.reduceFunc -- BEGIN";
	if (debug)
		cout << "Inside the reduceFunc function " << endl;

	cout << "Reducing key: " + iKey << endl;

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
		//LOG(ERROR) << "Reduce.reduceFunc -- Exception reducing";
		//LOG(ERROR) << e.what();
	}

	//LOG(INFO) << "Reduce.reduceFunc -- END";

	return 0;
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

// -------------------------------------------------------------------------------
// GetData
// -------------------------------------------------------------------------------
REDUCELIBRARY_API list<string> GetData()
{
	return _lstReducedData;
}