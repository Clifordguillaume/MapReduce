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
// ===============================================================================

// Local headers 
#include "Map.h"
#include "Reduce.h"
#include "FileManagement.h"

// Standard Library headers
#include <iostream>

using namespace std;

int main()
{
    string name = "";
    cout << "To get started please enter your name: ";
    cin >> name;
    cout << "\nHello " << name << " How are you this morning? \n\n";
}