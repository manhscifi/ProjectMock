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
};

