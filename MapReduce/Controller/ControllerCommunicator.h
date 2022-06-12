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
#pragma once
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
		int receiveData();

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