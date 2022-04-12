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
// ===============================================================================

// Local Headers
#include "Reduce.h"

#include <list>
#include <iostream>
#include <string>

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
Reduce::Reduce() 
{
	_pFileManagement = NULL;
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
	string sKeyVal = iKey;
	int iSum = 0;

	list<int>::iterator itr;

	for (itr = oLstOfData.begin(); itr != oLstOfData.end(); itr++)
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
	_pFileManagement = new FileManagement();
	// Write info to the file
	string fileName = "SUCCESS.txt";
	string sResult = to_string(iResult);

	string sFiledata = sKey + sResult; //("Skey", 1)

	_pFileManagement->writeToFile(fileName, sFiledata);
	
	return 0;
}