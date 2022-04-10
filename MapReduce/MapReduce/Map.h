// ===============================================================================
// CSE 687 MapReduce Project
// 
// Map.h
// 
// Author: Elizabeth and Cliford
// 
// Description: 
//              
// 
// Notes:
// 
// ===============================================================================
#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <vector>

using namespace std;

class Map
{
	public:
		Map();
		~Map();
		void map(string inputFileName, string outputFileName, string data);
		void writeKeyValueToFile(string outputFileName, string key, int value);

	private:
		vector<string> splitString(string str);
		string removeSpecialChars(string str);
		string lowerString(string str);
};
#endif /* MAP_H */