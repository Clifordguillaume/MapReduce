#pragma once
// ===============================================================================
// ReduceLibrary.h - Contains declarations of Reduce Functionalities
// 
// CSE 687 MapReduce Project 2
// 
// Executive.h
// 
// Author: Cliford
// 
// Description: The reduce class is responsible for taking in a key and an
//				iterator of integers, summing up the values of the iterator,
//				and exporting the results to a file in the user-specified output
//				directory.
// File History
// 5/02/22 - Cliford - Dll Initial creation
// ===============================================================================
#pragma once

#ifdef REDUCELIBRARY_EXPORTS
#define REDUCELIBRARY_API __declspec(dllexport)
#else
#define REDUCELIBRARY_API __declspec(dllimport)
#endif

#include<list>
#include <iostream>
using namespace std;

/**
* reduceFunc is used to simplified the data
* @param iKey - single key to retrieve the number of occurence for
* @param iLstOfData- input list to compare the key to to get the key value
* @return returns 0 to complete function task
*/
//TODO: To be removed later, does not like the virtual word
//extern "C" REDUCELIBRARY_API virtual int reduceFunc(string & iKey, list<int> iLstOfData);
extern "C" REDUCELIBRARY_API int reduceFunc(string & iKey, int* iLstOfData);


/**
 * exportFun is used to write the finalize data to a new file
 * @param sDataToWrite - the list of data that needs to be written to the file
 * @return int
 */
 //virtual int exportFunc(list<string> sDataToWrite, string outputFileDir);
extern "C" REDUCELIBRARY_API int exportFunc(list<string> sDataToWrite, string outputFileDir);


/**
 * GetData is used to retrieve the data that needs to be passed to
 *		  the next calling function
 * @param None
 * @return list<string>
 */
 //virtual list<string> GetData();
//extern "C" 
REDUCELIBRARY_API list<string> GetData();