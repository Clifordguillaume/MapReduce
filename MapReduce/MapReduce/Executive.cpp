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
// 4/24/22 - Elizabeth - Add glogs
// 4/25/22 - Elizabeth - Change main to use cmd prompt args
// ===============================================================================

// Local Headers
#include "Executive.h"
#include "Workflow.h"

// Standard Library headers
#include <glog/logging.h>

// for debugging purposes change to 0 to 
// not show cout messages in the cmd line
#define debug 0

using namespace std;
using namespace MapReduce;

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
    ::google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::INFO, "./logs/log");
    google::SetLogDestination(google::ERROR, "./logs/log");
    google::SetLogDestination(google::WARNING, "./logs/log");

    LOG(INFO) << "Starting MapReduce program...";
    cout << "Starting MapReduce program..." << endl;

    string inputFileDir;
    string outputFileDir;
    string tempOutputFileDir;

    if (argc == 4)
    {
        inputFileDir = argv[1];
        outputFileDir = argv[2];
        tempOutputFileDir = argv[3];
    }
    else {
        cout << "Invalid arguments passed. Usage: MapReduce.exe <inputFileDir> <outputFileDir> <tempOutputFileDir>" << endl;
        return 0;
    }

    LOG(INFO) << "User provided input file dir: " + inputFileDir;
    LOG(INFO) << "User provided output file dir: " + outputFileDir;
    LOG(INFO) << "User provided temp output file dir: " + tempOutputFileDir;
    if (debug)
        cout << "about to run the run function from the workflow class" << endl;

    Workflow workflow;
    workflow.run(inputFileDir, outputFileDir, tempOutputFileDir);

    LOG(INFO) << "MapReduce program completed running.";
    cout << "MapReduce program completed running." << endl;

    return 0;
}