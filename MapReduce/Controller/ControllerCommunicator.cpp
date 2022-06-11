// ===============================================================================
// CSE 687 MapReduce Project
// 
// ControllerCommunicator.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The ControllerCommunicator handles the connection for the Controller
// 
// File History:
// 6/5/22 - Elizabeth - Initial File with connectToStub(), disconnectStub(), 
//                      receiveData(), sendMessage()
// ===============================================================================
#define WIN32_LEAN_AND_MEAN

#include <ControllerCommunicator.h>
#include <windows.h>
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "ws2_32.lib")
#pragma warning(disable:4996)

#define BUFLEN 512

ControllerCommunicator::ControllerCommunicator(string ip, int port)
{
	this->ip = ip;
	this->port = port;
}

ControllerCommunicator::~ControllerCommunicator()
{
}

// -------------------------------------------------------------------------------
// connectToStub
// Based on: https://gist.github.com/sunmeat/02b60c8a3eaef3b8a0fb3c249d8686fd
// -------------------------------------------------------------------------------
int ControllerCommunicator::connectToStub()
{

    WSADATA ws;
    cout << "Initialising Winsock..." << endl;
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        cout << "Failed to initialize Winsock. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }
    cout << "Initialised Winsock." << endl;

    // create socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) // <<< UDP socket
    {
        cout << "socket() failed with error code: " << WSAGetLastError() << endl;
        return 1;
    }

    // setup address structure
    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port); // port of stub
    server.sin_addr.S_un.S_addr = inet_addr(ip.c_str()); // ip of stub

    return 0;
}

// -------------------------------------------------------------------------------
// disconnectStub
// -------------------------------------------------------------------------------
int ControllerCommunicator::disconnectStub()
{
    closesocket(client_socket);
    WSACleanup();

    return 0;
}

// -------------------------------------------------------------------------------
// receiveData
// Based on: https://gist.github.com/sunmeat/02b60c8a3eaef3b8a0fb3c249d8686fd
// -------------------------------------------------------------------------------
int ControllerCommunicator::receiveData()
{
    while (true)
    {
        // receive a reply and print it
        // clear the answer by filling null, it might have previously received data
        char message[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int slen = sizeof(sockaddr_in);
        int message_len;
        if (message_len = recvfrom(client_socket, message, BUFLEN, 0, (sockaddr*)&server, &slen) == SOCKET_ERROR)
        {
            cout << "recvfrom() failed with error code: " << WSAGetLastError() << endl;
            return 1;
        }

        cout << message << "\n";
    }

    return 0;
}

// -------------------------------------------------------------------------------
// sendMessage
// Based on: https://gist.github.com/sunmeat/02b60c8a3eaef3b8a0fb3c249d8686fd
// -------------------------------------------------------------------------------
int ControllerCommunicator::sendMessage(char message[])
{
    // send the message
    if (sendto(client_socket, message, strlen(message), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        cout << "sendto() failed with error code: " << WSAGetLastError() << endl;
        return 1;
    }

    return 0;
}