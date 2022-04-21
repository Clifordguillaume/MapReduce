// ===============================================================================
// CSE 687 MapReduce Project
// 
// BaseClass.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: This class holds shared variables between the sub classes
//
// File History:
// 04/20/22 - Elizabeth - Initial commit. Constructor and virtual Deconstructor
// ===============================================================================

// Local Headers
#include "BaseClass.h"
#include "FileManagement.h"

#include <algorithm>

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
BaseClass::BaseClass() 
{
	_pFileManagement = std::make_unique<FileManagement>();
}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
BaseClass::~BaseClass() 
{
}