#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include<iostream>
#include <string>
#include <winsock2.h>
#include"Macro.h"
using namespace std;

class TCPClient
{
private:    
    SOCKET clientSocket;
    SOCKADDR_IN clientAddr;
    int clientAddrSize;

public:
    TCPClient();

    bool connectToServer(string address, int port);

    bool sendDataToSever(string msg);

    string receiveDataFromSever();

    SOCKET getClientSocket();

    int getPort();

    void closeSocket(string str);

    bool setSockOpt()
    {
        DWORD timeout = SOCKET_RECV_TIMEOUT_SEC * 1000;
        if (setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0)
        {
            cout << "Setsockopt error.\n";
            return false;
        }
        return true;
    }
};

