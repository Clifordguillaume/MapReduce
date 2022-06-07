// ===============================================================================
// CSE 687 MapReduce Project
// 
// StubCommunicator.cpp
// 
// Author: Elizabeth and Cliford
// 
// Description: The StubCommunicator handles the connection for the Stub
// 
// File History:
// 6/5/22 - Elizabeth - Initial File with startListening(), startReceivingData(),
//                      sendMessage(), closeListener()
// ===============================================================================
#include "StubCommunicator.h"
#include <iostream>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") // Winsock Library
#pragma warning(disable:4996) 

#define BUFLEN 512

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

// -------------------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------------------
StubCommunicator::StubCommunicator(int port)
{
	this->port = port;
}

// -------------------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------------------
StubCommunicator::~StubCommunicator()
{
}

// -------------------------------------------------------------------------------
// startListening
// Based on: https://gist.github.com/sunmeat/02b60c8a3eaef3b8a0fb3c249d8686fd
// -------------------------------------------------------------------------------
int StubCommunicator::startListening()
{
    // initialise winsock
    WSADATA wsa;
    cout << "Initialising Winsock..." << endl;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cout << "Failed. Error Code: " << WSAGetLastError() << endl;
        exit(0);
    }
    cout << "Initialised." << endl;

    // create a socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        cout << "Could not create socket: " << WSAGetLastError() << endl;
    }
    cout << "Socket created." << endl;

    // prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // bind
    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        cout << "Bind failed with error code: " << WSAGetLastError() << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Bind done." << endl;
    return 0;
}

// -------------------------------------------------------------------------------
// startReceivingData
// Based on: https://gist.github.com/sunmeat/02b60c8a3eaef3b8a0fb3c249d8686fd
// -------------------------------------------------------------------------------
int StubCommunicator::startReceivingData()
{
    while (true)
    {
        cout << "Waiting for data..." << endl;
        fflush(stdout);
        char message[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int message_len;
        int slen = sizeof(sockaddr_in);
        if (message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
        {
            cout << "recvfrom() failed with error code: " << WSAGetLastError() << endl;
            exit(0);
        }

        // print details of the client/peer and the data received
        cout << "Received packet from " << inet_ntoa(client.sin_addr) << ":" << ntohs(client.sin_port) << endl;
        cout << "Data: " << message << endl;

        sendMessage("test2 sending reply");
    }
}

// -------------------------------------------------------------------------------
// sendMessage
// Based on: https://gist.github.com/sunmeat/02b60c8a3eaef3b8a0fb3c249d8686fd
// -------------------------------------------------------------------------------
int StubCommunicator::sendMessage(string msg)
{
    //cout << "type message to send: ";
    //cin.getline(message, BUFLEN);

    if (sendto(server_socket, msg.c_str(), strlen(msg.c_str()), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        cout << "sendto() failed with error code: " << WSAGetLastError() << endl;
        return 1;
    }

    return 0;
}

// -------------------------------------------------------------------------------
// closeListener
// -------------------------------------------------------------------------------
void StubCommunicator::closeListener()
{
    closesocket(server_socket);
    WSACleanup();
}