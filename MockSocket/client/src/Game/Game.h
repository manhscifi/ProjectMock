#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include"IO/IO.h"
#include"TCPClient.h"
#include <cstdlib>
#include<vector>
#include<sstream>
using namespace std;

class Game
{
private:
    //caro table
    TCPClient mClient;
    bool mStatusLogin;
	string mName;
    //
    vector<char> mCaro;
    int mSize;
    int mRemaining;
   
public:
    Game();
	//
	void login();
	void registerPlayer();
	void getInfo();
	void combat();
    void closeClient();
	//
	void clearGame();
    int inputPosition();
    bool isWinner(char symbol);
    //
    string removeAll(string str, const string& from);
    vector<string> splitString(string str, char splitter);
};

