#include "Game.h"

Game::Game()
{
    mCaro.assign(TABLE_SIZE * TABLE_SIZE, EMPTY);
    mSize = TABLE_SIZE;
    mRemaining = mSize * mSize;
    mStatusLogin = false;
}
//
void Game::login()
{
	if (mStatusLogin == true)
	{
		IO::colorize("You loged in already.\n", RED);
	}
	else
	{
		mClient.connectToServer("127.0.0.1", PORT);
		int count = 0;
		bool userbool = true;
		while (count < MAX_ATTEMPT && userbool == true)
		{
			mName = IO::inputName();
			mClient.sendDataToSever("login/username/" + mName);
			string res = mClient.receiveDataFromSever();
			if (res == "login/username/OK")
			{
				cout << "\tUsername OK\n";
				userbool = false;
			}
			else
			{
				cout << res << endl;
			}
			count++;
			if (count == MAX_ATTEMPT)
			{
				IO::colorize("Login fail. Please login again.\n", RED);
			}
		}

		count = 0;
		bool passbool = true;
		while (count < MAX_ATTEMPT && passbool == true)
		{
			string passWord = IO::inputPassWord();
			mClient.sendDataToSever("login/password/" + passWord);
			string res = mClient.receiveDataFromSever();
			if (res == "login/password/OK")
			{
				IO::colorize("You have loged in.\n", BLUE);
				mStatusLogin = true;
				passbool = false;
			}
			else
			{
				IO::colorize("Password incorrect.\n", RED);
			}
			count++;
			if (count == MAX_ATTEMPT)
			{
				IO::colorize("Login fail. Please login again.\n", RED);
			}
		}
	}
}
void Game::registerPlayer()
{
	if (mStatusLogin == true)
	{
		cout << "You loged in already.\n";
	}
	else
	{
		mClient.connectToServer("127.0.0.1", 5150);

		string name = IO::inputName();
		mClient.sendDataToSever("register/name/" + name);
		string res = mClient.receiveDataFromSever();
		//cout << res << endl;
		while (res.find("username/existed") != string::npos)
		{
			cout << "Username existed\n";
			name = IO::inputName();
			mClient.sendDataToSever("register/name/" + name);
			res = mClient.receiveDataFromSever();
		}

		string password = IO::inputPassWord();
		mClient.sendDataToSever("register/password/" + password);

		int age = IO::inputAge();
		mClient.sendDataToSever("register/age/" + to_string(age));

		string gender = IO::inputGender();
		mClient.sendDataToSever("register/gender/" + gender);

		string email = IO::inputEmail();
		mClient.sendDataToSever("register/email/" + email);
		res = mClient.receiveDataFromSever();

		while (res.find("email/existed") != std::string::npos)
		{
			cout << "Email existed\n";
			string email = IO::inputEmail();
			mClient.sendDataToSever("register/email/" + email);
			res = mClient.receiveDataFromSever();
		}

		mClient.sendDataToSever("register/done/");
	}
}
void Game::getInfo()
{
	if (mStatusLogin == false)
	{
		cout << "Log in please.\n";
	}
	else
	{
		mClient.sendDataToSever("getinfo/");
		string res = mClient.receiveDataFromSever();
		cout << "Rate - Win - Lose - Tie:\n";
		cout << res << endl;
	}
}
void Game::combat()
{
	if (mStatusLogin == true)
	{
		mClient.sendDataToSever("combat/");
		cout << "Please wait\n";
		//nhan tin da dc day vao room
		string res = mClient.receiveDataFromSever();
		cout << res << endl;

		char symyou = ' ', symother = ' ';

		res.pop_back();
		symyou = res.back();
		int turn = 0;
		if (symyou == symbolX)
		{
			symother = symbolO;
			turn = 0;
		}
		else if (symyou == symbolO)
		{
			symother = symbolX;
			turn = 1;
		}

		bool run = true;
		IO::printCaro(mCaro, " ");
		while (run)
		{
			if (turn % 2 == 0)
			{
				cout << symyou << " turn\n";
				int pos = inputPosition();
				string temp = "position/" + to_string(pos);

				mClient.sendDataToSever(temp);
				turn++;
				mRemaining--;
				system("cls");
				mCaro[pos] = symyou;
				IO::printCaro(mCaro, mName);
				if (isWinner(symyou))
				{
					cout << symyou << " is winner.\n";
					mClient.sendDataToSever("ketqua/win: " + string(1, symyou));
					run = false;
					continue;
				}
			}

			if (turn % 2 == 1)
			{
				cout << symother << " turn\n";
				string msg = mClient.receiveDataFromSever();
				int pos2 = stoi(removeAll(msg, "position/"));
				mCaro[pos2] = symother;
				system("cls");
				turn++;
				mRemaining--;
				IO::printCaro(mCaro, mName);
				if (isWinner(symother))
				{
					cout << symother << " is winner.\n";
					//client.sendDataToSever("ketqua/win: " + string(1, symother));
					run = false;
					continue;
				}
			}

			if (mRemaining == 0)
			{
				cout << "Tie\n";
				mClient.sendDataToSever("ketqua/Tie");
				run = false;
				continue;
			}
		}
		clearGame();
	}
	else
	{
		cout << "Log in please.\n";
	}
}
void Game::closeClient()
{
	if (mStatusLogin)
	{
		mStatusLogin = false;
		mClient.closeSocket();
	}
	else
	{
		cout << "Not log in\n";
	}
}
//
void Game::clearGame()
{
    mCaro.assign(TABLE_SIZE * TABLE_SIZE, EMPTY);
}
int Game::inputPosition()
{
    int position;
    cout<<"Type position : \n";
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
    for (int row = 1; row <=TABLE_SIZE; row++)
    {
        bool rowWin = true;
        for (int col = 1; col <=TABLE_SIZE - CONDITION_WIN + 1; col++)
        {
            rowWin = (mCaro[(row - 1) *TABLE_SIZE + (col - 1)] == symbol);
            rowWin = rowWin && (mCaro[(row - 1) *TABLE_SIZE + (col - 1 + 1)] == symbol);
            rowWin = rowWin && (mCaro[(row - 1) *TABLE_SIZE + (col - 1 + 2)] == symbol);
            rowWin = rowWin && (mCaro[(row - 1) *TABLE_SIZE + (col - 1 + 3)] == symbol);
            if (rowWin)
            {
                return true;
            }
        }
    }

    for (int row = 1; row <=TABLE_SIZE - CONDITION_WIN + 1; row++)
    {
        bool colWin = true;
        for (int col = 1; col <=TABLE_SIZE; col++)
        {
            colWin = (mCaro[(row - 1) *TABLE_SIZE + (col - 1)] == symbol);
            colWin = colWin && (mCaro[(row - 1 + 1) *TABLE_SIZE + (col - 1)] == symbol);
            colWin = colWin && (mCaro[(row - 1 + 2) *TABLE_SIZE + (col - 1)] == symbol);
            colWin = colWin && (mCaro[(row - 1 + 3) *TABLE_SIZE + (col - 1)] == symbol);
            if (colWin)
            {
                return true;
            }
        }
    }

    for (int row = 1; row <=TABLE_SIZE - CONDITION_WIN + 1; row++)
    {
        bool diaWin = true;
        for (int col = 1; col <=TABLE_SIZE - CONDITION_WIN + 1; col++)
        {
            diaWin = (mCaro[(row - 1) *TABLE_SIZE + (col - 1)] == symbol);
            diaWin = diaWin && (mCaro[(row - 1 + 1) *TABLE_SIZE + (col - 1 + 1)] == symbol);
            diaWin = diaWin && (mCaro[(row - 1 + 2) *TABLE_SIZE + (col - 1 + 2)] == symbol);
            diaWin = diaWin && (mCaro[(row - 1 + 3) *TABLE_SIZE + (col - 1 + 3)] == symbol);
            if (diaWin)
            {
                return true;
            }
        }
    }

    for (int row = 1; row <=TABLE_SIZE - CONDITION_WIN + 1; row++)
    {
        bool rDiaWin = true;
        for (int col =TABLE_SIZE; col >= CONDITION_WIN; col--)
        {
            rDiaWin = (mCaro[(row - 1) *TABLE_SIZE + (col - 1)] == symbol);
            rDiaWin = rDiaWin && (mCaro[(row - 1 + 1) *TABLE_SIZE + (col - 1 - 1)] == symbol);
            rDiaWin = rDiaWin && (mCaro[(row - 1 + 2) *TABLE_SIZE + (col - 1 - 2)] == symbol);
            rDiaWin = rDiaWin && (mCaro[(row - 1 + 3) *TABLE_SIZE + (col - 1 - 3)] == symbol);
            if (rDiaWin)
            {
                return true;
            }
        }
    }
    return false;
}
//
string Game::removeAll(string str, const string& from) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from)) != std::string::npos) {
        str.erase(start_pos, from.length());
    }
    return str;
}
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
