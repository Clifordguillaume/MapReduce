// ===============================================================================
// CSE 687 MapReduce Project
// 
// Reduce.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The reduce class is responsible for taking in a key and an
//				iterator of integers, summing up the values of the iterator,
//				and exporting the results to a file in the user-specified output
//				directory. 
// 
// File History:
// 4/10/22 - Cliford - Added reduceFunc(), exportFunc()
// 4/12/22 - Cliford - Added GetData()
// 4/20/22 - Elizabeth - Add filemanagement pointer, namespace
// 4/24/22 - Elizabeth - Add glogs, write final file to user defined output file
//						 dir
// ===============================================================================

// Local Headers
#include "Reduce.h"
#include <glog/logging.h>
#include <boost/algorithm/string.hpp>

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
			LOG(ERROR) << "Reduce.reduceFunc -- Exception reducing";
			LOG(ERROR) << e.what();
		}

		LOG(INFO) << "Reduce.reduceFunc -- END";

		return 0;
	}

	// -------------------------------------------------------------------------------
	// export
	// -------------------------------------------------------------------------------
	int Reduce::exportFunc(list<string> sDataToWrite, string outputFileDir)
	{
		LOG(INFO) << "Reduce.exportFunc -- BEGIN";
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