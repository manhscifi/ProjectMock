#include"TCPClient.h"

TCPClient::TCPClient()
{
    clientSocket = INVALID_SOCKET;
    clientAddr = SOCKADDR_IN();
    clientAddrSize = sizeof(clientAddr);
}

bool TCPClient::connectToServer(string address, int port)
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
        //cout << "Client: The Winsock DLL status is " << wsaData.szSystemStatus << endl;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET)
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
        // cout << "Client: socket() is OK!\n";
    }

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(port);
    clientAddr.sin_addr.s_addr = inet_addr(address.c_str());


    int connect_status = connect(clientSocket, (SOCKADDR*)&clientAddr, clientAddrSize);

    if (connect_status == SOCKET_ERROR)
    {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
        system("pause");
        // Exit with error
        return false;
    }
    else
    {
        cout << "Connected with Server's IP: " << inet_ntoa(clientAddr.sin_addr) << endl;
    }

    return true;
}

bool TCPClient::sendDataToSever(string msg)
{
    char* sendData = new char[msg.length() + 1];
    strcpy_s(sendData, msg.length() + 1, msg.c_str());
    if (send(clientSocket, sendData, msg.length() + 1, 0) < 0)
    {
        cout << "Send failed.\n";
        return false;
    }
    return true;
}

string TCPClient::receiveDataFromSever()
{
    char* rcvData = new char[BUFFER_LENGHT + 1];
    int byteReceived = recv(clientSocket, rcvData, BUFFER_LENGHT, 0);
    if (byteReceived > 0)
    {
        rcvData[BUFFER_LENGHT] = '\0';
        return string(rcvData);
    }
    else if (byteReceived <= 0)
    {
        cout << "Client: Connection closed with error code: " << WSAGetLastError() << endl;
        exit(1);
    }
    else
    {
        cout << "Client: recvfrom() failed with error code: " << WSAGetLastError() << endl;
        exit(1);
    }

    return " ";
}

SOCKET TCPClient::getClientSocket()
{
    return clientSocket;
}

int TCPClient::getPort()
{
    memset(&clientAddr, 0, clientAddrSize);

    getsockname(clientSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
    return htons(clientAddr.sin_port);
}

void TCPClient::closeSocket()
{
    bool closeSoc = false, leanupWSAC = false;
    if (closesocket(clientSocket) != 0)
    {
        cout << "Closesocket() failed! Error code: " << WSAGetLastError() << endl;
    }
    else
    {
        //cout << "Client: closesocket() is OK." << endl;
        closeSoc = true;
    }

    // When your application is finished call WSACleanup.
    //cout << "Client: Cleaning up..." << endl;
    if (WSACleanup() != 0)
    {
        cout << "WSACleanup() failed! Error code: " << WSAGetLastError() << endl;
    }
    else
    {
        //cout << "Client: WSACleanup() is OK." << endl;
        leanupWSAC = true;
    }

    if (closeSoc && leanupWSAC)
    {
        cout << "Loged out\n";
    }
}