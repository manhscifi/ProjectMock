#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include"Game/Game.h"
#include<iostream>
#include <string>
#include<thread>
#include"Macro.h"
using namespace std;

enum clientStatus
{
    statusFree = 0,
    statusBusy,
    statusCombat
};

enum RoomStatus
{
    statusFull = 0,
    statusNotFull,
    statusEmpty,
};

struct Client
{
    int client_socket;
    Player player;
    int status;
};

struct Room
{
    int roomID;
    vector<Client> clientInRoom;
    int roomStatus;
};

class TCPServer : public Game
{
private:

    SOCKET master_socket, new_socket;
    SOCKADDR_IN address;
    int addressSize;
    // 
    vector<Client> clientList;
    vector<Room*> roomList;

public:
    TCPServer();

    //reuse address
    bool setSockOpt();

    bool initListeningSocket(int port);
    //
    string receiveDataFromClient(int clientSocket);

    bool sendDataToClient(int clientSocket, string msg);
    //
    int getClientPort(int clientSocket);

    string removeAll(string str, const string& from);

    void processClientMessage(string msg, Client& client);

    void handleClient(Client client);

    Room* getAvailableRoom();

    void init(int port);

    void closeSocket(int socket);
};