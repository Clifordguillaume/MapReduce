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
// 4/12/22 - Cliford - Add sort and reduce calls
// 4/13/22 - Elizabeth - Move sort and reduce calls to Executive
// ===============================================================================

//// Local headers 
//#include "Workflow.h"
//
//// Standard Library headers
//#include <list>
//#include <iostream>
//
//using namespace std;
//
//int main(int argc, char** argv)
//{
//    //string inputFileDir = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\TestInputFileDir";
//    //string outputFileDir = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\TestOutputFileDir";
//    //string tempOutputFileDir = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\TestTempOutputFileDir";
//    //string inputFileName = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\testinput.txt";
//    //string outputFileName = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\testoutput.txt";
//
//    //string inputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testInput.txt";
//    //string outputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testoutput.txt";
//
//    //string inputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testInput.txt";
//    //string outputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testoutput.txt";
//    string inputFileDir = "C:\\Users\\clifguillaume\\Documents\\Object Oriented Projects\\TestData\\shakespeare";
//    string outputFileDir = "C:\\Users\\clifguillaume\\Documents\\Object Oriented Projects\\TestData\\OutputFileDir";
//    string tempOutputFileDir = "C:\\Users\\clifguillaume\\Documents\\Object Oriented Projects\\TestData\\TempDir";
//
//    // TODO: Make input and output file paths configurable via command line
//    /*if (argc > 2) 
//    {
//        inputFileDir = argv[1];
//        outputFileDir = argv[2];
//        tempOutputFileDir = argv[3];
//    }*/
//
//    Workflow workflow;
//    workflow.run(inputFileDir, outputFileDir, tempOutputFileDir);
//}