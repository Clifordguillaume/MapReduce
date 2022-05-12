#pragma once
// ===============================================================================
// ReduceLibrary.h - Contains declarations of Reduce Functionalities
// 
// CSE 687 MapReduce Project 2
// 
// Executive.h
// 
// Author: Cliford and Elizabeth
// 
// Description: The reduce class is responsible for taking in a key and an
//				iterator of integers, summing up the values of the iterator,
//				and exporting the results to a file in the user-specified output
//				directory.
// 
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
 * struct holding an array of reduced data and the quantity of data
 */
struct ReducedData
{
	// reduced data as strings
	string* reducedData;

	// number of rows of reduced data
	int numRows = 0;

	/**
	 * Constructor
	 * @param data - reduced data
	 * @param num - number of rows of reduced data
	 */
	ReducedData(string* data, int num)
	{
		reducedData = data;
		numRows = num;
	}
};

/**
* reduceFunc is used to simplified the data
* @param iKey - single key to retrieve the number of occurence for
* @param data - pointer to int array of values corresponding to iKey
* @param dataSize - the number of items in the data arr
* @return returns 0 to complete function task
*/
extern "C" REDUCELIBRARY_API int reduceFunc(string & iKey, int* data, int dataSize);


/**
 * exportFun is used to write the finalize data to a new file
 * @param sDataToWrite - the list of data that needs to be written to the file
 * @return int
 */
extern "C" REDUCELIBRARY_API int exportFunc(list<string> sDataToWrite, string outputFileDir);


/**
 * getData is used to retrieve the data that needs to be passed to
 *			the next calling function (write data to final file)
 * @return ReducedData struct containing a string pointer of string array containing data
 *			and the number of strings in the data array
 */
extern "C" REDUCELIBRARY_API ReducedData getData();