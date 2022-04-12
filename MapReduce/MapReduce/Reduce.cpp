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
// 4/10/22 - Cliford - Added reduceFunc(), export()
// ===============================================================================

// Local Headers
#include "Reduce.h"
#include "FileManagement.h"

#include <iostream>
#include <string>

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
Reduce::Reduce() 
{
	fileManagement = NULL;
}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
Reduce::~Reduce() {}

// -------------------------------------------------------------------------------
// reduceFunc
// -------------------------------------------------------------------------------
int Reduce::reduceFunc(string& sKey, vector<int>iIteratorVal)
{
	string sKeyVal = sKey;
	int iSum = 0;

	vector<int>::iterator itr;

	for (itr = iIteratorVal.begin(); itr <= iIteratorVal.end(); itr++) 
	{
		iSum = iSum + 1;
	}

	// write to file
	exportFunc(sKeyVal, iSum);

	return 0;
}

// -------------------------------------------------------------------------------
// export
// -------------------------------------------------------------------------------
int Reduce::exportFunc(string& sKey, int iResult)
{
	fileManagement = new FileManagement();
	// Write info to the file
	string fileName = "SUCCESS.txt";
	string sResult = to_string(iResult);

	string sFiledata = sKey + sResult; //("Skey", 1)

	fileManagement->writeToFile(fileName, sFiledata);

	return 0;
}