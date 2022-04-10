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
// ===============================================================================

// Local headers 
#include "Map.h"
#include "Reduce.h"
#include "FileManagement.h"

// Standard Library headers
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    string inputFileName = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\x64\\Debug\\testinput.txt";
    string outputFileName = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\x64\\Debug\\testoutput.txt";
    // TODO: Make input and output file paths configurable via command line
    /*if (argc > 2) 
    {
        inputFileName = argv[1];
        outputFileName = argv[2];
    }*/

    // read the input file contents
    FileManagement fileManager;
    string fileContents = fileManager.parseFile(inputFileName);

    // count the frequencies of the words in input file and write to output file
    Map map;
    map.map(inputFileName, outputFileName, fileContents);
}