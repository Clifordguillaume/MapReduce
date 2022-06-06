
#pragma once
#include <string>
#include <winsock2.h>

using namespace std;

class StubCommunicator
{
	public:
		StubCommunicator(int port);
		~StubCommunicator();
		int startListening();
		int startReceivingData();
		int sendMessage(string msg);
		void closeListener();

	private:
		string ip;
		int port;
		SOCKET server_socket;
		sockaddr_in server, client;
};