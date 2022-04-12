// ===============================================================================
// CSE 687 MapReduce Project
// 
// Reduce.h
// 
// Author: Elizabeth and Cliford
// 
// Description: 
//
// 
// File History:
// 4/10/22 - Cliford - Added reduceFunc(), export()
// ===============================================================================
#ifndef REDUCE_H
#define REDUCE_H

// Local Headers
#include "FileManagement.h"

// Standard Lirary Headers
#include <iostream>
#include <Vector>

using namespace std;

class Reduce
{
public:
	Reduce();
	~Reduce();

	/**
	 * reduceFunc is used to simplified the data
	 * @param iKey - single key to retrieve the number of occurence for
	 * @param iLstOfData- input list to compare the key to to get the key value
	 * @return int
	 */
	int reduceFunc(string& iKey, list<int> iLstOfData);

	/**
	 *
	 * @param sKey-
	 * @return int
	 */
	int exportFunc(string& sKey, int iResult);

private:

	FileManagement* _pFileManagement;

};
#endif /* REDUCE_H */