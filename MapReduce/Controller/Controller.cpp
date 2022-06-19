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
// 6/13/22 - Elizabeth - Add map threads
// 6/18/22 - Cliford - Added the Reducer communicator
// ===============================================================================
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <ControllerCommunicator.h>
#include <MessageUtils.h>
#include <FileManagement.h>
#include <iostream>
#include <thread>
#include <glog/logging.h>

using namespace std;

int main(int argc, char** argv)
{
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_INFO, "C:\MapReduceLogs");
    ::google::InitGoogleLogging(argv[0]);

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
    int ports[] = {1230, 1240, 1250};

    cout << "Building controllers..." << endl;
    ControllerCommunicator* cc1 = new ControllerCommunicator(ip, ports[0]); // 1230
    ControllerCommunicator* cc2 = new ControllerCommunicator(ip, ports[1]); // 1240
    ControllerCommunicator* cc3 = new ControllerCommunicator(ip, ports[2]); // 1250
    cout << "Built controllers" << endl;

    cout << "Connecting to stubs..." << endl;
    int connResult1 = cc1->connectToStub();
    int connResult2 = cc2->connectToStub();
    int connResult3 = cc3->connectToStub();

    std::thread t1;
    std::thread t2;
    std::thread t3;

    // clear the temp output file dir before beginning the mapping and reducing
    FileManagement::clearDirectory(tempOutputFileDir);

    // Mapper Stub 1 (port 1230)
    int msgSize1;
    char* msg1 = MessageUtils::encodeMessage(0, inputFileDir1, outputFileDir, tempOutputFileDir, msgSize1);
    if (connResult1 == 0)
    {
        cout << "Sending message to stub 1" << endl;
        cc1->sendMessage(msg1, msgSize1);
        t1 = std::thread([cc1, ports] { cc1->receiveData(ports[0]); }); // thread to continuously receive data from stub
    }

    // Mapper Stub 2 (port 1240)
    int msgSize2;
    char* msg2 = MessageUtils::encodeMessage(0, inputFileDir2, outputFileDir, tempOutputFileDir, msgSize2);
    if (connResult2 == 0)
    {
        cout << "Sending message to stub 2" << endl;
        cc2->sendMessage(msg2, msgSize2);
        t2 = std::thread([cc2, ports] { cc2->receiveData(ports[1]); });; // thread to continuously receive data from stub
    }

    // if mappers created, wait for the mappers to return "done" before proceeding to reduce
    if (t1.joinable()) { t1.join(); }
    if (t2.joinable()) { t2.join(); }

    cout << "Both mappers done mapping" << endl;

    // Reducer Stub 3 (port 1250)
    int msgSize3;
    char* msg3 = MessageUtils::encodeMessage(1, inputFileDir1, outputFileDir, tempOutputFileDir, msgSize3);
    if (connResult3 == 0)
    {
        cout << "Sending message to stub 3" << endl;
        cc3->sendMessage(msg3, msgSize3);
        t3 = std::thread([cc3, ports] { cc3->receiveData(ports[2]); });; // thread to continuously receive data from stub
    }

    // if reduce process is created, wait for reduce to return "done" before proceeding on
    if (t3.joinable()) { t3.join(); }


    cout << "MapReduce complete. Results can be found in: " << outputFileDir << endl;

}