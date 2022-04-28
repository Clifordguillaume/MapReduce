// ===============================================================================
// CSE 687 MapReduce Project
// 
// Sorter.h
// 
// Author: Elizabeth and Cliford
// 
// Description: The Sorter class is responsible for taking in inputs containing
//				keys and one value per key, and sorting it in alphabetical order.
// 
// ===============================================================================

#ifndef SORTER_H
#define SORTER_H

// Local Headers
#include "FileManagement.h"

#include <iostream>
#include <list>

using namespace std;

namespace MapReduce
{
	class Sorter
	{
		public:
			FileManagement* _pFileManagement;

			Sorter();
			Sorter(FileManagement* _pFM) : _pFileManagement(_pFM) {}
			virtual ~Sorter();

			/**
			 * sort is used to read and sort the data in the file passed in as the input
			 * @param iFilePath - the file that need to be sorted
			 * @return int - returns 0 to complete function task
			 */
			int sort(string& iFilePath);

		private:

	};
}
#endif /* SORTER_H */