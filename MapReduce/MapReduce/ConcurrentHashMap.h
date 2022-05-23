// ===============================================================================
// CSE 687 MapReduce Project
// 
// ConcurrentHashMap.h
// 
// Author: Elizabeth and Cliford
// 
// Description: Class used to wrap a map into a thread safe data strucutre
// 
// ===============================================================================

#ifndef CONCURRENTHASHMAP_H
#define CONCURRENTHASHMAP_H

// Local Headers
#include "ReduceLibrary.h"
#include <mutex>
#include <map>

using namespace std;

namespace MapReduce
{
	class ConcurrentHashMap
	{
		public:
			/**
			 * Add data from ReducedData to map
			 * @param reducedData - data to add
			 */
			static void addToMap(ReducedData reducedData);

			/**
			 * Get key-values from map as list of strings
			 * @return list of strings representing map contents
			 */
			static list<string> getMapContents();

		private:

	};
}
#endif /* CONCURRENTHASHMAP_H */
