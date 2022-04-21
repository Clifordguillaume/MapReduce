// ===============================================================================
// CSE 687 MapReduce Project
// 
// BaseClass.h
// 
// Author: Elizabeth and Cliford
// 
// Description: This class holds shared variables between the sub classes
// ===============================================================================
#ifndef BASECLASS_H
#define BASECLASS_H

#include "FileManagement.h"
#include <memory>

using namespace std;

class BaseClass
{
	public:
		std::unique_ptr<FileManagement> _pFileManagement;

		BaseClass();
		virtual ~BaseClass();

	private:
};
#endif /* BASECLASS_H */