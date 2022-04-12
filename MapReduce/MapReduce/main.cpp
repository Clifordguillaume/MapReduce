// ===============================================================================
// CSE 687 MapReduce Project
// 
// maim.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: Contains the 'main' function. Program execution begins and ends 
//              there.
// 
// Notes:
// 
// File History:
// 4/8/22 - Elizabeth - Initial main
// 4/10/22 - Elizabeth - Move main functions to Executive
// ===============================================================================

// Local headers 
#include "Executive.h"
#include "SortingClass.h"
#include "Reduce.h"
#include "Map.h"

// Standard Library headers
#include <list>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    //string inputFileName = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\x64\\Debug\\testinput.txt";
    //string outputFileName = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\x64\\Debug\\testoutput.txt";
    //string inputFileName = "testoutput.txt";

    string inputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testInput.txt";
    string outputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testoutput.txt";

    // TODO: Make input and output file paths configurable via command line
    // TODO: Make inputFileName inputFileDirectory
    /*if (argc > 2) 
    {
        inputFileName = argv[1];
        outputFileName = argv[2];
    }*/

    Executive executor;
    executor.run(inputFileName, outputFileName);

    SortingClass sortingclass;
    list<string> lstOfData = sortingclass.Sort(outputFileName);
 
    // preview what's in the file
    int lstSize = lstOfData.size();
    for (auto it = lstOfData.begin(); it != lstOfData.end(); it++)
    {
        cout << *it << endl;

        // Get key from the list value
        Map map;
        string sKey = map.getKey(*it);

        list<int> itr = map.getKeyValue(sKey, lstOfData);

        Reduce reduce;
        reduce.reduceFunc(sKey, itr);

    }


}