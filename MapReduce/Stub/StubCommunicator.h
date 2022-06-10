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
#include <vector>
#include <winsock2.h>
#include "../MapReduce/Workflow.h")
#include "StubWorker.h"

using namespace std;
using namespace MapReduce;

class StubCommunicator
{
	public:
		// Pointer to StubWorker to handle mapping/reducing
		StubWorker* _pStubWorker;

		StubCommunicator(int port);
		~StubCommunicator();

		/* 
		 * Create the socket and bind to it
		 */
		int startListening();

		/*
		 * Continuously receive messages from the socket
		 */
		int receiveData();

		/*
		 * Send a message to the Controller
		 * @param msg - message to send
		 */
		int sendStatus(char status[]);

		/*
		 * Check if the stub job (map or reduce) has completed yet
		 */
		bool isDoneExecuting();

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

		// flag indicating if stub job (map or reduce) has completed yet
		bool done;

		string command;
		string inputFileDir;
		string outputFileDir;
		string tempOutputFileDir;
};