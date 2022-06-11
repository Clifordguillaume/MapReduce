// ===============================================================================
// CSE 687 MapReduce Project
// 
// Stub.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The Stub contains the main file to execute for each stub
// 
// File History:
// 6/5/22 - Elizabeth - Initial File
// 6/9/22 - Elizabeth - Add threads receiveData and heartbeat 
// ===============================================================================
//#undef _HAS_STD_BYTE
#define GLOG_NO_ABBREVIATED_SEVERITIES
#define _HAS_STD_BYTE 0

#include "StubCommunicator.h"
#include <iostream>
#include <thread>
#include <functional>
#include <glog/logging.h>

using namespace Stub;

// represents the status of the stub job
union Status {
    int running[2]{ 0 };
    char status[8]; // done or not done
};

int main(int argc, char** argv)
{
    FLAGS_logtostderr = true;
    google::SetLogDestination(google::GLOG_INFO, "./logs/log");
    ::google::InitGoogleLogging(argv[0]);

    int port = atoi(argv[1]);

    // create stub communicator with stub's port
    StubCommunicator* communicator = new StubCommunicator(port);
    int startResult = communicator->startListening();
    cout << (startResult == 0 ? "Stub started listening" : "Stub failed to start listening") << endl;

    // create thread to continuously receive data from the controller
    std::thread t1([communicator] { communicator->receiveData(); });
    t1.detach();

    std::thread t2([communicator]
        {
            int i = 0;
            Status status;
            while (true)
            {
                auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000); // send status every 1 second
                
                if (!communicator->hasReceivedData())
                {
                    cout << "Controller has not sent command yet" << endl;

                }
                else 
                {
                    cout << "\rCommunicator not done executing: " << i++;
                    status.running[0] = 1; // stub is now running
                    status.running[1] = communicator->isDoneExecuting() ? 1 : 0; // send current done flag value at this iteration of the loop
                    communicator->sendStatus(status.status); // send the status to the communicator
                }

                std::this_thread::sleep_until(x);
            }
            cout << "Stub done executing" << endl;
        });
    t2.detach();

    while (true);

    return 0;
}
