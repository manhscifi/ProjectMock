#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include<iostream>
#include <string>
#include <winsock2.h>

using namespace std;

const int BUFFER_LENGHT = 1024;

class TCPServer
{
private:
    SOCKET serverSocket, clientSocketAccepted;
    SOCKADDR_IN ServerAddr, clientAddr;
    string msgFromClientOut;
    char msgFromClient[BUFFER_LENGHT];
public:
    TCPServer()
    {
        serverSocket = clientSocketAccepted = INVALID_SOCKET;
        ServerAddr = clientAddr = SOCKADDR_IN();
    }

    bool accecptClient(int port)
    {
        WSADATA	wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            cout << "Client: WSAStartup failed with error: " << WSAGetLastError() << endl;
            // Clean up
            WSACleanup();
            system("pause");
            // Exit with error
            return false;
        }
        else
        {
            cout << "Server: The Winsock DLL status is " << wsaData.szSystemStatus << endl;
        }

        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (serverSocket == INVALID_SOCKET)
        {
            cout << "Server: Error at socket(): " << WSAGetLastError() << endl;
            // Clean up
            WSACleanup();
            system("pause");
            // Exit with error
            return false;
        }
        else
        {
            cout << "Server: socket() is OK!" << endl;
        }

        // Set up a SOCKADDR_IN structure that will tell bind that we
        // want to receive datagrams from all interfaces using port 5150.
        // The IPv4 family
        ServerAddr.sin_family = AF_INET;
        // Port no. 5150
        ServerAddr.sin_port = htons(port);
        // From all interface (0.0.0.0) // INADDR_ANY
        ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        int ServerAddrSize = sizeof(ServerAddr);
        if (bind(serverSocket, (LPSOCKADDR)&ServerAddr, ServerAddrSize) == SOCKET_ERROR)
        {
            cout << "Server: bind() failed! Error: " << WSAGetLastError() << endl;
            // Close the socket
            closesocket(serverSocket);
            // Do the clean up
            WSACleanup();
            system("pause");
            // and exit with error
            return false;
        }
        else
        {
            cout << "Server: bind() is OK!\n";
        }

        int listen_status = listen(serverSocket, 1);
        if (listen_status == SOCKET_ERROR) 
        {
            cout << "listen failed with error: " << WSAGetLastError() << endl;
            closesocket(serverSocket);
            WSACleanup();
            system("pause");
            return false;
        }

        int clientAddrSize = sizeof(clientAddr);
        clientSocketAccepted = accept(serverSocket, (LPSOCKADDR)&clientAddr, &clientAddrSize);

        if (clientSocketAccepted == INVALID_SOCKET) {
            cout << "Accept failed with error :" << WSAGetLastError() << endl;
            closesocket(clientSocketAccepted);
            WSACleanup();
            system("pause");
            return false;
        }
        else
        {
            cout << "Server: Conneted to client " << htons(clientAddr.sin_port) << endl;
        }

        cout << "Server: Ready...\n\n";

        return true;
    }
    int sendDataToClient(char msg[BUFFER_LENGHT])
    {
        /*return send(clientSocketAccepted, msg, BUFFER_LENGHT, 0);*/
        if (send(clientSocketAccepted, msg, BUFFER_LENGHT, 0) < 0)
        {
            cout << "Send failed.\n";
            return false;
        }
        return true;
    }
    int receiveDataFromClient()
    {    
        int byte = recv(clientSocketAccepted, msgFromClient, BUFFER_LENGHT, 0);
        if (byte > 0)
        {
            cout << "byte: " << byte << endl;            
            return true;
        }
        else if (byte <= 0)
        {
            cout << "Server: Connection closed with error code: " << WSAGetLastError() << endl;
        }
        else
        {
            cout << "Server: recvfrom() failed with error code: " << WSAGetLastError() << endl;
        }
        return false;
    }
    string getmsgFromServer()
    {
        return msgFromClient;
    }
    SOCKET getClientSocketAccepted()
    {
        return clientSocketAccepted;
    }
    void closeSocket()
    {
        closesocket(clientSocketAccepted);
        WSACleanup();
    }
    bool returnAccecptClient(int port)
    {
        WSADATA	wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            cout << "Client: WSAStartup failed with error: " << WSAGetLastError() << endl;
            // Clean up
            WSACleanup();
            system("pause");
            // Exit with error
            return false;
        }
        else
        {
            cout << "Server: The Winsock DLL status is " << wsaData.szSystemStatus << endl;
        }

        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (serverSocket == INVALID_SOCKET)
        {
            cout << "Client: Error at socket(): " << WSAGetLastError() << endl;
            // Clean up
            WSACleanup();
            system("pause");
            // Exit with error
            return false;
        }
        else
        {
            cout << "Server: socket() is OK!" << endl;
        }

        // Set up a SOCKADDR_IN structure that will tell bind that we
        // want to receive datagrams from all interfaces using port 5150.
        // The IPv4 family
        ServerAddr.sin_family = AF_INET;
        // Port no. 5150
        ServerAddr.sin_port = htons(port);
        // From all interface (0.0.0.0) // INADDR_ANY
        ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        int ServerAddrSize = sizeof(ServerAddr);
        if (bind(serverSocket, (LPSOCKADDR)&ServerAddr, ServerAddrSize) == SOCKET_ERROR)
        {
            cout << "Server: bind() failed! Error: " << WSAGetLastError() << endl;
            // Close the socket
            closesocket(serverSocket);
            // Do the clean up
            WSACleanup();
            system("pause");
            // and exit with error
            return false;
        }
        else
        {
            cout << "Server: bind() is OK!\n";
        }

        int listen_status = listen(serverSocket, 1);
        if (listen_status == SOCKET_ERROR) {
            cout << "listen failed with error: " << WSAGetLastError() << endl;
            closesocket(serverSocket);
            WSACleanup();
            system("pause");
            return false;
        }

        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (LPSOCKADDR)&clientAddr, &clientAddrSize);

        if (clientSocketAccepted == INVALID_SOCKET) {
            cout << "accept failed with error :" << WSAGetLastError() << endl;
            closesocket(clientSocket);
            WSACleanup();
            system("pause");
            return false;
        }
        else
        {
            cout << "Server: Conneted to client " << htons(clientAddr.sin_port) << endl;
        }

        cout << "Server: Ready...\n\n";

        return clientSocket;
    }
};

