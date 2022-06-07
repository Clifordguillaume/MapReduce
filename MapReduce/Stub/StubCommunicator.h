// ===============================================================================
// CSE 687 MapReduce Project
// 
// StubCommunicator.h
// 
// Author: Elizabeth and Cliford
// 
// Description: The StubCommunicator handles the connection for the Stub
// 
// ===============================================================================
#pragma once
#include <string>
#include <winsock2.h>

using namespace std;

class StubCommunicator
{
	public:
		StubCommunicator(int port);
		~StubCommunicator();

		/* 
		 * Create the socket and bind to it
		 */
		int startListening();

		/*
		 * Continuously receive messages from the socket
		 */
		int startReceivingData();

		/*
		 * Send a message to the Controller
		 * @param msg - message to send
		 */
		int sendMessage(string msg);

		/*
		 * Close the socket
		 */
		void closeListener();

	private:
		// port
		int port;

		// socket
		SOCKET server_socket;

		// socket addresses
		sockaddr_in server, client;
};