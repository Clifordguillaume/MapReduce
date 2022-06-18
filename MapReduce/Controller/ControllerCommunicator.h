// ===============================================================================
// CSE 687 MapReduce Project
// 
// ControllerCommunicator.h
// 
// Author: Elizabeth and Cliford
// 
// Description: The ControllerCommunicator handles the connection for the Controller
// 
// ===============================================================================
#ifndef CONTROLLER_COMMUNICATOR_H
#define CONTROLLER_COMMUNICATOR_H

#include <string>
#include <winsock2.h>

using namespace std;

class ControllerCommunicator
{
	public:
		ControllerCommunicator(string ip, int port);
		~ControllerCommunicator();

		/*
		 * Connect to a stub
		 */
		int connectToStub();

		/*
		 * Disconnect from a stub
		 */
		int disconnectStub();

		/*
		 * Receive data from a stub
		 */
		int receiveData(int stubId);

		/*
		 * Send a message to a stub
		 */
		int sendMessage(char message[], int size);

	private:
		string ip;
		int port;
		int client_socket;
		sockaddr_in server;
};
#endif /* CONTROLLER_COMMUNICATOR_H */