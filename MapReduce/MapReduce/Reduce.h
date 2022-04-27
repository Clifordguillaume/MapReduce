// ===============================================================================
// CSE 687 MapReduce Project
// 
// Reduce.h
// 
// Author: Elizabeth and Cliford
// 
// Description: 
//
// ===============================================================================
#ifndef REDUCE_H
#define REDUCE_H

// Local Headers
#include "FileManagement.h"

// Standard Lirary Headers
#include <iostream>
#include <Vector>

using namespace std;

namespace MapReduce
{
	class Reduce
	{
		public:
			FileManagement* _pFileManagement;

			Reduce();
			Reduce(FileManagement* _pFM) : _pFileManagement(_pFM) {}
			virtual ~Reduce();

			/**
			 * reduceFunc is used to simplified the data
			 * @param iKey - single key to retrieve the number of occurence for
			 * @param iLstOfData- input list to compare the key to to get the key value
			 * @return int
			 */
			virtual int reduceFunc(string& iKey, list<int> iLstOfData);

			/**
			 * exportFun is used to write the finalize data to a new file
			 * @param sDataToWrite - the list of data that needs to be written to the file
			 * @return int
			 */
			virtual int exportFunc(list<string> sDataToWrite, string outputFileDir);

			/**
			 * GetData is used to retrieve the data that needs to be passed to
			 *		  the next calling function
			 * @param None
			 * @return list<string>
			 */
			virtual list<string> GetData();

		private:
			list<string> _lstReducedData;

	};
}
#endif /* REDUCE_H */