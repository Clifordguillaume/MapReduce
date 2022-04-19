// ===============================================================================
// CSE 687 MapReduce Project
// 
// Executive.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The Executive receives input from the user via command line
//				and passes the data to the workflow.
// 
// File History:
// 4/10/22 - Elizabeth - Moved main functions into new run method and decouple 
//			             map and file manager
// 4/13/22 - Elizabeth - MOVED sort and reduce functions from main to Executive
// 4/13/22 - Elizabeth - Condense run() into separate map(), sort(), reduce(). 
//                       Remove writeMapOutput()
// 4/14/22 - Elizabeth - Remove run(), map(), sort(), reduce() from Executive and
//						 to relocate to Workflow
// 4/18/22 - Cliford - Removed main from main.cpp and include it on here.
// ===============================================================================

// Local Headers
#include "Executive.h"
#include "Workflow.h"

//// Standard Library headers
//#include <list>
//#include <iostream>

using namespace std;

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
Executive::Executive()
{
}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
Executive::~Executive() 
{
}


int main(int argc, char** argv)
{
    //string inputFileDir = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\TestInputFileDir";
    //string outputFileDir = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\TestOutputFileDir";
    //string tempOutputFileDir = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\TestTempOutputFileDir";
    //string inputFileName = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\testinput.txt";
    //string outputFileName = "C:\\Users\\dwuli\\OneDrive\\egrad\\EDwulit Projects\\MapReduce\\MapReduce\\testoutput.txt";

    //string inputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testInput.txt";
    //string outputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testoutput.txt";

    //string inputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testInput.txt";
    //string outputFileName = "C:\\Users\\clifguillaume\\Documents\\TestData\\testoutput.txt";
    //string inputFileDir = "C:\\Users\\clifguillaume\\Documents\\Object Oriented Projects\\TestData\\shakespeare";
    //string outputFileDir = "C:\\Users\\clifguillaume\\Documents\\Object Oriented Projects\\TestData\\OutputFileDir";
    //string tempOutputFileDir = "C:\\Users\\clifguillaume\\Documents\\Object Oriented Projects\\TestData\\TempDir";

    string inputFileDir = "C:\\Users\\clifguillaume\\Documents\\Object Oriented Projects\\MapReduce\\MapReduce\\MapReduce\\TestInputFileDir";
    string outputFileDir = "C:\\Users\\clifguillaume\\Documents\\Object Oriented Projects\\MapReduce\\MapReduce\\MapReduce\\TestOutputFileDir";
    string tempOutputFileDir = "C:\\Users\\clifguillaume\\Documents\\Object Oriented Projects\\MapReduce\\MapReduce\\MapReduce\\TestTempOutputFileDir";


    // TODO: Make input and output file paths configurable via command line
    /*if (argc > 2)
    {s
        inputFileDir = argv[1];
        outputFileDir = argv[2];
        tempOutputFileDir = argv[3];
    }*/

    Workflow workflow;
    workflow.run(inputFileDir, outputFileDir, tempOutputFileDir);
}