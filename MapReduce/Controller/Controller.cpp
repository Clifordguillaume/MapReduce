// ===============================================================================
// CSE 687 MapReduce Project
// 
// Controller.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The Controller contains the main for the controller
// 
// File History:
// 6/5/22 - Elizabeth - Initial File
// 6/11/22 - Elizabeth - Add all controller communicators and their handling
// ===============================================================================
#include <ControllerCommunicator.h>
#include <MessageUtils.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    string inputFileDir1;
    string inputFileDir2;
    string outputFileDir;
    string tempOutputFileDir;
    if (argc == 5)
    {
        inputFileDir1 = argv[1];
        inputFileDir2 = argv[2];
        outputFileDir = argv[3];
        tempOutputFileDir = argv[4];
    }
    else {
        cout << "Invalid arguments passed. Usage: MapReduce.exe <inputFileDir> <outputFileDir> <tempOutputFileDir>" << endl;
        return 0;
    }

    string ip = "127.0.0.1"; // FIXED IP

    cout << "Building controllers..." << endl;
    ControllerCommunicator cc1(ip, 1230); // FIXED PORT DEF FOR STUB
    ControllerCommunicator cc2(ip, 1240); // FIXED PORT DEF FOR STUB
    ControllerCommunicator cc3(ip, 1250); // FIXED PORT DEF FOR STUB
    cout << "Built controllers" << endl;

    cout << "Connecting to stubs..." << endl;
    int connResult1 = cc1.connectToStub();
    int connResult2 = cc2.connectToStub();
    int connResult3 = cc3.connectToStub();

    // Mapper Stub 1
    int msgSize1;
    char* msg1 = MessageUtils::encodeMessage(0, inputFileDir1, outputFileDir, tempOutputFileDir, msgSize1);
    if (connResult1 == 0)
    {
        cout << "Sending message to stub 1" << endl;
        int sendResult1 = cc1.sendMessage(msg1, msgSize1);
        cc1.receiveData();
    }

    // Mapper Stub 2
    int msgSize2;
    char* msg2 = MessageUtils::encodeMessage(0, inputFileDir2, outputFileDir, tempOutputFileDir, msgSize2);
    if (connResult2 == 0)
    {
        cout << "Sending message to stub 2" << endl;
        int sendResult1 = cc1.sendMessage(msg2, msgSize2);
        cc2.receiveData();
    }

    // Reducer Stub
    int msgSize3;
    char* msg3 = MessageUtils::encodeMessage(1, inputFileDir1, outputFileDir, tempOutputFileDir, msgSize3);
    if (connResult3 == 0)
    {
        cout << "Sending message to stub 3" << endl;
        int sendResult1 = cc1.sendMessage(msg3, msgSize3);
        cc3.receiveData();
    }

}