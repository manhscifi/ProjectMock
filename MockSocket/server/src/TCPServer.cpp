#include"TCPServer.h"

TCPServer::TCPServer()
{
    master_socket = new_socket = 0;
    address = SOCKADDR_IN();
    addressSize = sizeof(address);
    loadPlayerList();
}

//reuse address
bool TCPServer::setSockOpt()
{
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&OPTION, sizeof(OPTION)) < 0)
    {
        perror("setsockopt");
        return false;
    }
    return true;
}

bool TCPServer::initListeningSocket(int port)
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

    master_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (master_socket == INVALID_SOCKET)
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
    address.sin_family = AF_INET;
    // Port no. 5150
    address.sin_port = htons(port);
    // From all interface (0.0.0.0) // INADDR_ANY
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(master_socket, (LPSOCKADDR)&address, addressSize) == SOCKET_ERROR)
    {
        cout << "Server: bind() failed! Error: " << WSAGetLastError() << endl;
        // Close the socket
        closesocket(master_socket);
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

    int listen_status = listen(master_socket, 1);
    if (listen_status == SOCKET_ERROR)
    {
        cout << "listen failed with error: " << WSAGetLastError() << endl;
        closesocket(master_socket);
        WSACleanup();
        system("pause");
        return false;
    }

    //accept the incoming connection 
    puts("Waiting for connections ...");

    return true;
}
//
string TCPServer::receiveDataFromClient(int clientSocket)
{
    //inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    char* rcvData = new char[BUFFER_LENGHT + 1];
    //int byte = recv(clientSocket, msg, sizeof(msg), 0);
    int byte = recv(clientSocket, rcvData, BUFFER_LENGHT, 0);
    if (byte <= 0)
    {
        cout << "[-] Server: client port " << getClientPort(clientSocket) << " disconneted.\n";
        closeSocket(clientSocket);
    }
    else if (byte > 0)
    {
        rcvData[BUFFER_LENGHT] = '\0';
        return string(rcvData);
    }
    else
    {
        cout << "Server: receive from client " << getClientPort(clientSocket) << " failed\n";
    }
    return " ";
}

bool TCPServer::sendDataToClient(int clientSocket, string msg)
{
    char* sendData = new char[msg.length() + 1];
    //strcpy(sendData,  msg.c_str());
    strcpy_s(sendData, msg.length() + 1, msg.c_str());

    if (send(clientSocket, sendData, msg.length() + 1, 0) < 0)
    {
        cout << "Send failed.\n";
        return false;
    }
    return true;
}
//
void TCPServer::processClientMessage(string msg, Client& client)
{
    // handle log  in
    if (msg.find("login/") != string::npos)
    {
        string login = removeAll(msg, "login/");
        if (login.find("username/") != string::npos)
        {
            string name = removeAll(login, "username/");
            if (isNameInList(name))
            {
                sendDataToClient(client.client_socket, "login/username/OK");
                client.player = *(mPlayerList[name]);

            }
            else if (!isNameInList(name))
            {
                sendDataToClient(client.client_socket,
                    "Username '" + name + "' is not in database.");
            }
        }
        if (login.find("password/") != string::npos)
        {
            string password = removeAll(login, "password/");
            //cout << "password nhan: " << password << endl;
            //cout << "password datat base " << client.player.getPassWord() << endl;
            //cout << "kq so sanh " << (password == client.player.getPassWord()) << endl;
            if (password == client.player.getPassWord())
            {
                sendDataToClient(client.client_socket, "login/password/OK");
            }
            else
            {
                sendDataToClient(client.client_socket, "login/password/fail");
            }
        }
    }
    // handle for getting information
    if (msg.find("getinfo/") != string::npos)
    {
        string result;
        for (auto i = mPlayerList.begin(); i != mPlayerList.end(); i++)
        {
            if (client.player.getName() == i->first)
            {
                result = i->second->getRate() + " - " + to_string(i->second->getWin())
                    + " - " + to_string(i->second->getLose()) + " - " + to_string(i->second->getTie());
            }
        }

        sendDataToClient(client.client_socket, result);
    }
    // handle for register
    if (msg.find("register/") != string::npos)
    {
        string msg2 = removeAll(msg, "register/");
        if (msg2.find("name/") != string::npos)
        {
            string name = removeAll(msg2, "name/");
            if (isNameInList(name) == 1)
            {
                sendDataToClient(client.client_socket, "username/existed");
            }
            else
            {
                client.player.setName(name);
                sendDataToClient(client.client_socket, "username/OK");
                cout << "set name " << name << endl;
            }
        }
        if (msg2.find("password/") != string::npos)
        {
            string name = removeAll(msg2, "password/");
            client.player.setPassWord(name);
        }
        if (msg2.find("age/") != string::npos)
        {
            int age = stoi(removeAll(msg2, "age/"));
            client.player.setAge(age);
            cout << "set age " << age << endl;
        }
        if (msg2.find("gender/") != string::npos)
        {
            string gender = removeAll(msg2, "gender/");
            client.player.setGender(gender);
            cout << "set gender " << gender << endl;
        }
        if (msg2.find("email/") != string::npos)
        {
            string email = removeAll(msg2, "email/");
            cout << "kq check trung mail " << isEmailInList(email) << endl;
            if (isEmailInList(email) == 1)
            {
                sendDataToClient(client.client_socket, "email/existed");
            }
            else
            {
                cout << msg2 << endl;
                client.player.setEmail(email);
                sendDataToClient(client.client_socket, "email/OK");
                cout << "set mail " << email << endl;
            }
        }

        if (msg2.find("done/") != string::npos)
        {
            mPlayerList[client.player.getName()] = make_shared<Player>(client.player);
            //cout << "add " << client.player.getName() << endl;
            //showPlayers();
            //cout << "add to mPlayerList " << mPlayerList.size() << endl;
            updatePlayerList();
        }
    }
    //        
    if (msg.find("combat/") != string::npos)
    {
        //client.status = statusCombat;             
        Room* tempRoom = getAvailableRoom();
        tempRoom->clientInRoom.push_back(client);
        if (tempRoom->clientInRoom.size() == MAX_CLIENTS_IN_ROOM)
        {
            tempRoom->roomStatus = statusFull;
            Client temp = (client.client_socket == tempRoom->clientInRoom[0].client_socket) ?
                tempRoom->clientInRoom[1] : tempRoom->clientInRoom[0];
            sendDataToClient(client.client_socket, temp.player.getName() + " is X. You are O.");
            sendDataToClient(temp.client_socket, client.player.getName() + " is O. You are X.");
        }
        else
        {
            tempRoom->roomStatus = statusNotFull;
            /*sendDataToClient(client.client_socket,
                "Please wait!");*/
        }
    }
    if (msg.find("position/") != string::npos)
    {
        Client temp;
        for (unsigned i = 0; i < roomList.size(); i++)
        {
            if (client.client_socket == roomList[i]->clientInRoom[0].client_socket ||
                client.client_socket == roomList[i]->clientInRoom[1].client_socket)
            {
                temp = (client.client_socket == roomList[i]->clientInRoom[0].client_socket) ?
                    roomList[i]->clientInRoom[1] : roomList[i]->clientInRoom[0];
            }
        }
        //cout << "receive '" << msg << "' from: " << getClientPort(client.client_socket) << endl;
        string pos = removeAll(msg, "position/");
        sendDataToClient(temp.client_socket, pos);
        //cout << "send '" << pos << "' to: " << getClientPort(temp.client_socket) << endl;

    }
    if (msg.find("ketqua/") != string::npos)
    {
        Client temp;
        for (unsigned i = 0; i < roomList.size(); i++)
        {
            if (client.client_socket == roomList[i]->clientInRoom[0].client_socket ||
                client.client_socket == roomList[i]->clientInRoom[1].client_socket)
            {
                temp = (client.client_socket == roomList[i]->clientInRoom[0].client_socket) ?
                    roomList[i]->clientInRoom[1] : roomList[i]->clientInRoom[0];
            }
        }
        string pos = removeAll(msg, "ketqua/");
        cout << "receive '" << pos << "' from: " << getClientPort(client.client_socket) << endl;
        if (pos == "win: X")
        {
            client.player.increaseWin();
            temp.player.increaseLose();
        }
        else if (pos == "win: O")
        {
            temp.player.increaseWin();
            client.player.increaseLose();
        }
        else
        {
            temp.player.increaseTie();
            client.player.increaseTie();
        }

        mPlayerList[temp.player.getName()] = make_shared<Player>(temp.player);
        mPlayerList[client.player.getName()] = make_shared<Player>(client.player);
        updatePlayerList();
    }
}

void TCPServer::handleClient(Client client)
{
    char* rcvData = new char[BUFFER_LENGHT + 1];
    int byte;
    while (byte = recv(client.client_socket, rcvData, BUFFER_LENGHT, 0) > 0)
    {
        rcvData[BUFFER_LENGHT] = '\0';
        processClientMessage(string(rcvData), client);
    }
    if (byte <= 0)
    {
        cout << "[-] Server: client port " << getClientPort(client.client_socket) << " disconneted.\n";
        delete[]rcvData;
        closeSocket(client.client_socket);

    }
    /*if (closesocket(client.client_socket) == SOCKET_ERROR)
    {
        delete[]rcvData;
        cout << "Closesocket() failed" << endl;
    }*/
}

Room* TCPServer::getAvailableRoom()
{
    for (auto i = roomList.begin(); i != roomList.end(); i++)
    {
        if ((*i)->roomStatus == statusNotFull || (*i)->roomStatus == statusEmpty)
        {
            return (*i);
            break;
        }
    }
    static int i = 1;
    Room* room = new Room();
    room->roomID = i;
    i++;
    roomList.push_back(room);
    return room;
}

void TCPServer::init(int port)
{
    loadPlayerList();
    initListeningSocket(port);
    while (true)
    {
        if ((new_socket = accept(master_socket, (LPSOCKADDR)&address, &addressSize)) < 0)
        {
            closesocket(new_socket);
            cout << "Accept() failed" << endl;
            system("pause");
            exit(1);
        }

        cout << "[+] Client port " << ntohs(address.sin_port) << " connected\n";
        Client client;
        client.client_socket = new_socket;
        clientList.push_back(client);

        thread* clientThread = new thread(&TCPServer::handleClient, this, client);
    }
}

void TCPServer::closeSocket(int socket)
{
    //Close the socket and mark as 0 in list for reuse
    closesocket(socket);
    for (auto i = clientList.begin(); i != clientList.end(); i++)
    {
        if ((*i).client_socket == socket)
        {
            clientList.erase(i);
            break;
        }
    }
    for (auto i = roomList.begin(); i != roomList.end(); i++)
    {
        for (auto j = (*i)->clientInRoom.begin(); j != (*i)->clientInRoom.end(); j++)
        {
            if (socket == (*j).client_socket)
            {
                (*i)->clientInRoom.erase(j);
                break;
            }
        }
    }
    for (auto i = roomList.begin(); i != roomList.end(); i++)
    {
        if ((*i)->clientInRoom.size() == 0)
        {
            delete (*i);
            break;
        }
    }
}

//
int TCPServer::getClientPort(int clientSocket)
{
    SOCKADDR_IN temp;
    int tempSize = sizeof(temp);
    //inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    getpeername(clientSocket, (sockaddr*)&temp, &tempSize);
    return ntohs(temp.sin_port);
}
//
string TCPServer::removeAll(string str, const string& from) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from)) != string::npos) {
        str.erase(start_pos, from.length());
    }
    return str;
}