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
#include <map>

using namespace std;

class Map
{
	public:
		Map();
		~Map();
		std::map<string, int> map(string inputFileName, string data);

	private:
		vector<string> splitString(string str);
		string removeSpecialChars(string str);
		string lowerString(string str);
};
#endif /* MAP_H */