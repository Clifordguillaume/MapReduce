// Stub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//#undef _HAS_STD_BYTE
#define _HAS_STD_BYTE 0

#include "StubCommunicator.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    int port = atoi(argv[1]);

    StubCommunicator communicator(port);
    int startResult = communicator.startListening();
    cout << (startResult == 0 ? "started listening" : "failed to start listening") << endl;
    communicator.startReceivingData(); // new thread
    // thread for heartbeat
}