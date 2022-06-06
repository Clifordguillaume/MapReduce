#define WIN32_LEAN_AND_MEAN

#include <ControllerCommunicator.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 1024

ControllerCommunicator::ControllerCommunicator(string ip, string port)
{
	this->ip = ip;
	this->port = port;
}

ControllerCommunicator::~ControllerCommunicator()
{

}

// https://docs.microsoft.com/en-us/windows/win32/winsock/complete-client-code
int ControllerCommunicator::connectToStub()
{
    int iResult;

    WSADATA wsaData;
    ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL;
    struct addrinfo addressInfo, hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;

    // Resolve the server address and port
    iResult = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result); // pass in ip and port
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Connect to server.
    iResult = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(ConnectSocket);
        //ConnectSocket = INVALID_SOCKET;
    }

    return 0;
}

int ControllerCommunicator::disconnectStub()
{
    // shutdown the connection since no more data will be sent
    int iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}

int ControllerCommunicator::receiveData()
{
    int iResult;
    char recvbuf[DEFAULT_BUFLEN];\
    int recvbuflen = DEFAULT_BUFLEN;
    memset(recvbuf, 0, recvbuflen);
    // Receive until the peer closes the connection
    //do {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            string msg = recvbuf;
            printf("Bytes received: %d\n", iResult);
            cout << "Msg received: " << msg << endl;
        }
        else if (iResult == 0)
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

   // } while (iResult > 0);

    return 0;
}

int ControllerCommunicator::sendInstructions(string instruction)
{
    // Send an initial buffer
    int iResult = send(ConnectSocket, instruction.c_str(), instruction.length(), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    return 0;
}