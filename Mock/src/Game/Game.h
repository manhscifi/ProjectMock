#pragma once
#include<algorithm>
#include<windows.h>
#include <filesystem>
#include<fstream>
#include<map>
#include"Player/Player.h"
#include"IO/IO.h"
#include <cstdlib>
using namespace std;
namespace fs = filesystem;

class Game
{
private:
    //caro table
    vector<char> mCaro;
    int mSize;
    int mRemaining;
    //players
    Player mOne;
    Player mTwo;
    //data record
    map<string, shared_ptr<Player>> mPlayerList;
    vector<string> mGameRecord;
public:
    Game();
    void initGame();
    //
    void registerPlayer();
    bool isNameInList(const string& name);
    bool isEmailInList(const string& email);
    //
    void clearGame();
    int inputPosition(string player);
    bool isWinner(char symbol);
    void playGame();
    //
    void loadPlayerList();
    void updatePlayerList();
    //sort players by rate
    void showPlayers();
    //
    void loadMatchRecord();
    void updateMatchRecord();
    void replayMatch();
    //
    static bool comparePlayersByRate(shared_ptr<Player>& a, shared_ptr<Player>& b);
    vector<string> splitString(string str, char splitter);
};

