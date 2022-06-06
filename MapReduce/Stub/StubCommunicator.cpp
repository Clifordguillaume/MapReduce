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

// https://gist.github.com/sunmeat/02b60c8a3eaef3b8a0fb3c249d8686fd
int StubCommunicator::startListening()
{
    // initialise winsock
    WSADATA wsa;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        exit(0);
    }
    printf("Initialised.\n");

    // create a socket
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket: %d", WSAGetLastError());
    }
    printf("Socket created.\n");

    // prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // bind
    if (bind(server_socket, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code: %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done.");
}

int StubCommunicator::startReceivingData()
{
    while (true)
    {
        printf("Waiting for data...");
        fflush(stdout);
        char message[BUFLEN] = {};

        // try to receive some data, this is a blocking call
        int message_len;
        int slen = sizeof(sockaddr_in);
        if (message_len = recvfrom(server_socket, message, BUFLEN, 0, (sockaddr*)&client, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code: %d", WSAGetLastError());
            exit(0);
        }

        // print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        printf("Data: %s\n", message);

        sendMessage("test2 sending reply");
    }
}

int StubCommunicator::sendMessage(string msg)
{
    //cout << "type message to send: ";
    //cin.getline(message, BUFLEN);

    if (sendto(server_socket, msg.c_str(), strlen(msg.c_str()), 0, (sockaddr*)&client, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code: %d", WSAGetLastError());
        return 1;
    }

    return 0;
}

void StubCommunicator::closeListener()
{
    closesocket(server_socket);
    WSACleanup();
}