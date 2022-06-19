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

#ifndef STUB_COMMUNICATOR_H
#define STUB_COMMUNICATOR_H

#include <string>
#include <vector>
#include <winsock2.h>
#include "../MapReduce/Workflow.h")
#include "StubWorker.h"

using namespace std;

namespace Stub
{
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
			 * Send a status message to the Controller
			 * @isRunning - flag indicating if stub has started processing
			 * @isDone - flag indicating if stub job has completed
			 */
			int sendStatus(int isDone);

			/*
			 * Check if the stub has received any data from the Controller yet
			 */
			bool hasReceivedData();

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

			// flag indicating if received data
			bool receivedData;

			// flag indicating if stub job (map or reduce) has completed yet
			bool done;

			string command;
			string inputFileDir;
			string outputFileDir;
			string tempOutputFileDir;
	};
}
#endif /* STUB_COMMUNICATOR_H */
