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
// ===============================================================================
#include <ControllerCommunicator.h>
#include <iostream>

using namespace std;

int main()
{
    string ip = "127.0.0.1";
    string ports[] = {"1230", "1240", "1250"}; // fixed ports for the stubs

    cout << "building controller" << endl;
    ControllerCommunicator cc(ip, 1234); // TODO: Create a controller communicator for each stub
    cout << "built controller" << endl;
    int connResult = cc.connectToStub();
    cout << (connResult == 0 ? "connected to stub" : "failed to connect to stub") << endl;
    for (int i = 0; i < 10; i++)
    {
        char msg[] = { '9', '2' };
        int sendResult = cc.sendMessage(msg);
        cout << (sendResult == 0 ? "sent data" : "failed to send data") << endl;
        cc.receiveData();
    }
}