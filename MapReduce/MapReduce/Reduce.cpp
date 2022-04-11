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

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
Reduce::Reduce() 
{
}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
Reduce::~Reduce() {}

//// -------------------------------------------------------------------------------
//// reduceFunc
//// -------------------------------------------------------------------------------
//int Reduce::reduceFunc(string sKey, ) 
//{
//	return 0;
//}
//
//// -------------------------------------------------------------------------------
//// export
//// -------------------------------------------------------------------------------
//int Reduce::export(string sKey, ) 
//{
//	return 0;
//}