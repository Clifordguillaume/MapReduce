
#pragma once
#include <string>
#include <winsock2.h>

using namespace std;

class ControllerCommunicator
{
	public:
		ControllerCommunicator(string ip, string port);
		~ControllerCommunicator();
		int connectToStub();
		int disconnectStub();
		int receiveData();
		int sendInstructions(string instruction);

	private:
		string ip;
		string port;
		SOCKET ConnectSocket;
};