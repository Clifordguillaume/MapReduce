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
// ===============================================================================

// Local Headers
#include "Executive.h"

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

