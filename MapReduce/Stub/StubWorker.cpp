// ===============================================================================
// CSE 687 MapReduce Project
// 
// StubWorker.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The StubWorker contains the main file to execute for each stub
// 
// File History:
// 6/9/22 - Elizabeth - Initial file. Created handleMessage() with map handling,
//                      isDoneExecuting(), markDone()
// ===============================================================================
#include "StubWorker.h"
#include "StringUtils.h"
#include <iostream>
#include "../MapReduce/Workflow.h")
#include <boost/bind.hpp>
#include <boost/function.hpp>

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
StubWorker::StubWorker()
{
}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
StubWorker::~StubWorker()
{
    delete _pWorkflow;
}

// -------------------------------------------------------------------------------
// handleMessage
// -------------------------------------------------------------------------------
void StubWorker::handleMessage(string msg)
{
    // received command, not "done" yet
    done = false;

    // parse the message if it is not empty
    vector<string> msgContents = StringUtils::parseMessage(msg);
    command = msgContents[0];
    inputFileDir = msgContents[1];
    outputFileDir = msgContents[2];
    tempOutputFileDir = msgContents[3];

    // determine what command was issued and act accordingly
    int cmd = stoi(command);
    if (cmd == 0)  // map
    {
        // create func pointer to callback and mark the done flag when map() in Workflow has completed
        boost::function<void(StubWorker*)> fnc_ptr = boost::bind(&StubWorker::markDone, _1);

        _pWorkflow->map(inputFileDir, tempOutputFileDir, fnc_ptr, this);
    }
    else if (cmd == 1)  // reduce]
    {
        // TODO: create reduce callback similar to map
        _pWorkflow->reduce(tempOutputFileDir, outputFileDir);
    }
    else { // unknown command
        cout << "Unknown command received: " << command << endl;
    }
}

// -------------------------------------------------------------------------------
// markDone
// -------------------------------------------------------------------------------
void StubWorker::markDone()
{
    done = true;
}

// -------------------------------------------------------------------------------
// isDoneExecuting
// -------------------------------------------------------------------------------
bool StubWorker::isDoneExecuting()
{
    return done;
}
