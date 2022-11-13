#include "Game.h"

Game::Game()
{
    if (!is_directory(DATABASE_DIR))
    {
        create_directories(DATABASE_DIR);
    }
}

bool Game::isNameInList(const string& name)
{
    for (auto i = mPlayerList.begin(); i != mPlayerList.end(); i++)
    {
        if (name == i->first)
        {
            return true;
        }
    }
    return false;
}
bool Game::isEmailInList(const string& email)
{
    for (auto i = mPlayerList.begin(); i != mPlayerList.end(); i++)
    {
        if (email == i->second->getEmail())
        {
            return true;
        }
    }
    return false;
}

//
void Game::loadPlayerList()
{
    ifstream myfile(PLAYERS_DATABASE);
    if (myfile.is_open())
    {
        if (myfile.peek() != EOF)
        {
            string line;
            while (getline(myfile, line))
            {
                vector<string> result = splitString(line, '-');
                string name = result[0];
                string passWord = result[1];
                int win = stoi(result[2]);
                int lose = stoi(result[3]);
                int tie = stoi(result[4]);
                int age = stoi(result[5]);
                string gender = result[6];
                string email = result[7];
                shared_ptr<Player> player = make_shared<Player>(name, passWord, win, lose, tie, age, gender, email);
                mPlayerList.insert({ name, player });
            }
        }
        myfile.close();
    }
    else
    {
        ofstream myfile(PLAYERS_DATABASE);
        if (myfile.is_open())
        {            
            myfile.close();
        }
        else
        {
            cout << "Unable to create players data file.\n";
        }
    }
}
void Game::updatePlayerList()
{
    ofstream myfile(PLAYERS_DATABASE);
    if (myfile.is_open() && mPlayerList.size())
    {
        for (auto i = mPlayerList.begin(); i != mPlayerList.end(); i++)
        {
            string line = i->first + "-" + i->second->getPassWord() + "-" +
                to_string(i->second->getWin()) + "-" +
                to_string(i->second->getLose()) + "-" + to_string(i->second->getTie()) + "-" +
                to_string(i->second->getAge()) + "-" + i->second->getGender() + "-" + 
                i->second->getEmail() + "\n";
            myfile << line;
        }
        myfile.close();
    }
}
//sort players by rate
bool Game::comparePlayersByRate(shared_ptr<Player>& a, shared_ptr<Player>& b)
{
    float rateA = static_cast<float>(a->getWin()) / (a->getWin() + a->getLose() + a->getTie());
    float rateB = static_cast<float>(b->getWin()) / (b->getWin() + b->getLose() + b->getTie());
    if (rateA > rateB)
    {
        return true;
    }
    return false;
}
//
void Game::loadMatchRecord()
{
    ifstream myfile(REPLAY_DATABASE);
    if (myfile.is_open())
    {
        if (myfile.peek() != EOF)
        {
            string line;
            while (getline(myfile, line))
            {
                mGameRecord.push_back(line);
            }
        }
        myfile.close();
    }
    else
    {
        ofstream myfile(REPLAY_DATABASE);
        if (myfile.is_open())
        {
            myfile.close();
        }
        else
        {
            cout << "Unable to create replay data file.\n";
        }
    }
}
void Game::updateMatchRecord()
{
    ofstream myfile(REPLAY_DATABASE); //to overwrite data
    if (myfile.is_open() && mGameRecord.size())
    {
        myfile << mGameRecord[mGameRecord.size() - 1] + "\n";
        for (auto i = mGameRecord.begin(); i < mGameRecord.end() - 1; i++)
        {
            myfile << (*i) + "\n";
        }
        myfile.close();
    }
}

//
vector<string> Game::splitString(string str, char splitter)
{
    vector<string> result;
    string current = "";
    for (unsigned i = 0; i < str.size(); i++) {
        if (str[i] == splitter) {
            if (current != "") {
                result.push_back(current);
                current = "";
            }
            continue;
        }
        current += str[i];
    }
    if (current.size() != 0)
        result.push_back(current);
    return result;
}
