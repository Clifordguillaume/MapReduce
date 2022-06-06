// Controller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ControllerCommunicator.h>
#include <iostream>

using namespace std;

int main()
{
    string ip = "127.0.0.1";
    string ports[] = {"1230", "1240", "1250"};

    cout << "building controller" << endl;
    ControllerCommunicator cc(ip, "1234");
    cout << "built controller" << endl;
    int connResult = cc.connectToStub();
    cout << (connResult == 0 ? "connected to stub" : "failed to connect to stub") << endl;
    for (int i = 0; i < 10; i++)
    {
        int sendResult = cc.sendInstructions("test1");
        cout << (sendResult == 0 ? "sent data" : "failed to send data") << endl;
        cc.receiveData();
    }
}