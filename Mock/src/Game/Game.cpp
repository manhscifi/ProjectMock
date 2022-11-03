#include "Game.h"

Game::Game()
{
    mCaro.assign(SIZE * SIZE, EMPTY);
    mSize = SIZE;
    mRemaining = mSize * mSize;
    if (!fs::is_directory(DATABASE_DIR))
    {
        fs::create_directories(DATABASE_DIR);
    }
}
void Game::registerPlayer()
{
    string name, email;
    bool validName, validEmail;
    do
    {
        name = IO::inputName();
        validName = !isNameInList(name);
        if (!validName)
        {
            cout << "\tName existed.\n";
        }
    } while (!validName);
    int age = IO::inputAge();
    string gender = IO::inputGender();
    do
    {
        email = IO::inputEmail();
        validEmail = !isEmailInList(email);
        if (!validEmail)
        {
            cout << "\tEmail existed.\n";
        }
    } while (!validEmail);
    shared_ptr<Player> player = make_shared<Player>(name, age, gender, email);
    mPlayerList[name] = player;
    Sleep(200);
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
void Game::initGame()
{
    if (mPlayerList.size() >= 2)
    {
        cout << "Player 1\n";
        string name1, name2;
        bool valid;
        do
        {
            name1 = IO::inputName();
            valid = isNameInList(name1);
            if (!valid)
            {
                cout << "Name not exist.\n";
            }
        } while (!valid);
        char selection = IO::inputSymbol();
        cout << "Player 2\n";
        do
        {
            name2 = IO::inputName();
            transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
            transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
            valid = (name1 != name2) && isNameInList(name2);
            if (!valid)
            {
                cout << "\tIdentical name/Name not exist.\n";
            }
        } while (!valid);

        mOne = *(mPlayerList[name1]);
        mTwo = *(mPlayerList[name2]);
        if (toupper(selection) == symbolX)
        {
            mOne.setSymbol(symbolX);
            mTwo.setSymbol(symbolO);
        }
        else
        {
            mOne.setSymbol(symbolO);
            mTwo.setSymbol(symbolX);
        }
    }
    else
    {
        cout << "Register at least 2 new players to start\n";
        cout << "Player in database: " << mPlayerList.size() << endl;
        if (mPlayerList.size() == 1)
        {
            registerPlayer();
        }
        if (mPlayerList.size() == 0)
        {
            registerPlayer();
            cout << "\t---------\n";
            registerPlayer();
        }
        cout << "Let's start...\n";
        Sleep(1000);
        system("cls");
        initGame();
    }
}
void Game::clearGame()
{
    mCaro.assign(SIZE * SIZE, EMPTY);
}
int Game::inputPosition(string player)
{
    int position;
    cout << player << " type position: \n";
    bool valid;
    do
    {
        position = IO::inputPosition();
        valid = mCaro[position] == EMPTY;

        if (!valid)
        {
            cout << "Occupied cell.\n";
        }
    } while (!valid);
    return position;
}
bool Game::isWinner(char symbol)
{
    for (int row = 1; row <= SIZE; row++)
    {
        bool rowWin = true;
        for (int col = 1; col <= SIZE - CONDITION_WIN + 1; col++)
        {
            rowWin = (mCaro[(row - 1) * SIZE + (col - 1)] == symbol);
            rowWin = rowWin && (mCaro[(row - 1) * SIZE + (col - 1 + 1)] == symbol);
            rowWin = rowWin && (mCaro[(row - 1) * SIZE + (col - 1 + 2)] == symbol);
            rowWin = rowWin && (mCaro[(row - 1) * SIZE + (col - 1 + 3)] == symbol);
            if (rowWin)
            {
                return true;
            }
        }
    }

    for (int row = 1; row <= SIZE - CONDITION_WIN + 1; row++)
    {
        bool colWin = true;
        for (int col = 1; col <= SIZE; col++)
        {
            colWin = (mCaro[(row - 1) * SIZE + (col - 1)] == symbol);
            colWin = colWin && (mCaro[(row - 1 + 1) * SIZE + (col - 1)] == symbol);
            colWin = colWin && (mCaro[(row - 1 + 2) * SIZE + (col - 1)] == symbol);
            colWin = colWin && (mCaro[(row - 1 + 3) * SIZE + (col - 1)] == symbol);
            if (colWin)
            {
                return true;
            }
        }
    }

    for (int row = 1; row <= SIZE - CONDITION_WIN + 1; row++)
    {
        bool diaWin = true;
        for (int col = 1; col <= SIZE - CONDITION_WIN + 1; col++)
        {
            diaWin = (mCaro[(row - 1) * SIZE + (col - 1)] == symbol);
            diaWin = diaWin && (mCaro[(row - 1 + 1) * SIZE + (col - 1 + 1)] == symbol);
            diaWin = diaWin && (mCaro[(row - 1 + 2) * SIZE + (col - 1 + 2)] == symbol);
            diaWin = diaWin && (mCaro[(row - 1 + 3) * SIZE + (col - 1 + 3)] == symbol);
            if (diaWin)
            {
                return true;
            }
        }
    }

    for (int row = 1; row <= SIZE - CONDITION_WIN + 1; row++)
    {
        bool rDiaWin = true;
        for (int col = SIZE; col >= CONDITION_WIN; col--)
        {
            rDiaWin = (mCaro[(row - 1) * SIZE + (col - 1)] == symbol);
            rDiaWin = rDiaWin && (mCaro[(row - 1 + 1) * SIZE + (col - 1 - 1)] == symbol);
            rDiaWin = rDiaWin && (mCaro[(row - 1 + 2) * SIZE + (col - 1 - 2)] == symbol);
            rDiaWin = rDiaWin && (mCaro[(row - 1 + 3) * SIZE + (col - 1 - 3)] == symbol);
            if (rDiaWin)
            {
                return true;
            }
        }
    }
    return false;
}
void Game::playGame()
{
    int turn = 0;
    bool run = true;
    string record = "";
    string title = "\tPlayer 1 - " + string(1, mOne.getSymbol()) +
        " | Player 2 - " + string(1, mTwo.getSymbol());
    system("cls");
    IO::printCaro(mCaro, title);
    while (run)
    {
        if (turn % 2 == 0)
        {
            int position = inputPosition("Player 1");//player input position
            mOne.play(mCaro, position);
            record += string(1, mOne.getSymbol()) + "-" + to_string(position) + "-";
            mRemaining--; //number of empty cells decreases
            turn++;
            system("cls");
            IO::printCaro(mCaro, title);
            if (isWinner(mOne.getSymbol()))
            {
                cout << mOne.getSymbol() << " is winner.\n";                
                mOne.increaseWin();
                mTwo.increaseLose();
                run = false;
                continue;
            }
        }

        if (turn % 2 == 1)
        {
            int position = inputPosition("Player 2");
            mTwo.play(mCaro, position);
            record += string(1, mTwo.getSymbol()) + "-" + to_string(position) + "-";
            mRemaining--;
            turn++;
            system("cls");
            IO::printCaro(mCaro, title);
            if (isWinner(mTwo.getSymbol()))
            {
                cout << mTwo.getSymbol() << " is winner.\n";
                mTwo.increaseWin();
                mOne.increaseLose();
                run = false;
                continue;
            }
        }

        if (mRemaining == 0)
        {
            cout << "Tie.\n";
            mTwo.increaseTie();
            mOne.increaseTie();
            run = false;
        }
    }
    record.pop_back();
    mGameRecord.push_back(record);
    mPlayerList[mOne.getName()] = make_shared<Player>(mOne);
    mPlayerList[mTwo.getName()] = make_shared<Player>(mTwo);
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
                int win = stoi(result[1]);
                int lose = stoi(result[2]);
                int tie = stoi(result[3]);
                int age = stoi(result[4]);
                string gender = result[5];
                string email = result[6];
                shared_ptr<Player> player = make_shared<Player>(name, win, lose, tie, age, gender, email);
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
            string line = i->first + "-" + to_string(i->second->getWin()) + "-" +
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
void Game::showPlayers()
{
    if (mPlayerList.size())
    {
        vector<shared_ptr<Player>> temp;
        for (auto i = mPlayerList.begin(); i != mPlayerList.end(); i++)
        {
            temp.push_back(i->second);
        }
        sort(temp.begin(), temp.end(), &comparePlayersByRate);

        int count = 1;
        for (auto i = temp.begin(); i != temp.end(); i++)
        {
            cout << "[";
            IO::colorize(to_string(count), BLUE);
            cout<< "] ";
            IO::printPlayer((*i)->getName(), (*i)->getRate(), (*i)->getWin(), (*i)->getLose(), (*i)->getTie());
            count++;
        }
    }
    else
    {
        cout << "Empty\n";
    }
}
//
void  Game::loadMatchRecord()
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
void Game::replayMatch()
{
    if (mGameRecord.size())
    {
        vector<char> tempCaro;
        string title = "\tRePlaying Previous Games";
        tempCaro.assign(SIZE * SIZE, EMPTY);
        for (unsigned i = 0; i < mGameRecord.size(); i++)
        {
            vector<string> temp = splitString(mGameRecord[i], '-');
            for (unsigned j = 0; j < temp.size(); j += 2)
            {
                IO::printCaro(tempCaro, title);
                tempCaro[stoi(temp[j + 1])] = temp[j][0];
                Sleep(1000);
                system("cls");
            }
            IO::printCaro(tempCaro, title);
            if (i != mGameRecord.size() - 1)
            {
                cout << "Next match...\n";
                Sleep(2500);
                tempCaro.assign(SIZE * SIZE, EMPTY);
                system("cls");
            }

        }
    }
    else
    {
        cout << "Empty\n";
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
