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
// 4/13/22 - Elizabeth - Added try-catch
// ===============================================================================

// Local Headers
#include "Reduce.h"

// STL Heades 
#include <list>
#include <iostream>
#include <string>

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
Reduce::~Reduce() {}

// -------------------------------------------------------------------------------
// reduceFunc
// -------------------------------------------------------------------------------
int Reduce::reduceFunc(string& iKey, list<int> oLstOfData)
{
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
		cout << "Exception reducing" << endl;
	}

	return 0;
}

// -------------------------------------------------------------------------------
// export
// -------------------------------------------------------------------------------
int Reduce::exportFunc(list<string> sDataToWrite)
{
	// Write info to the file
	string fileName = "SUCCESS.txt";

	// remove duplicates
	sDataToWrite.unique();
	_pFileManagement->writeToFile(fileName, sDataToWrite);
	
	return 0;
}

// -------------------------------------------------------------------------------
// GetData
// -------------------------------------------------------------------------------
list<string>  Reduce::GetData() 
{
	return _lstReducedData;
}