#pragma once
#include<algorithm>
#include<windows.h>
#include <filesystem>
#include<fstream>
#include<map>
#include"Player/Player.h"
#include <cstdlib>
using namespace std;
using namespace filesystem;

class Game
{
protected:
    map<string, shared_ptr<Player>> mPlayerList;
    vector<string> mGameRecord;
public:

    Game();
    //
    bool isNameInList(const string& name);
    bool isEmailInList(const string& email);
    //
    bool isWinner(char symbol);
    //
    void loadPlayerList();
    void updatePlayerList();
    //
    void loadMatchRecord();
    void updateMatchRecord();
    void replayMatch();
    //
    static bool comparePlayersByRate(shared_ptr<Player>& a, shared_ptr<Player>& b);
    vector<string> splitString(string str, char splitter);
};

