#include "Player/Player.h"

Player::Player()
{
	mName = "";
	mPassWord = "";
	mAge = 0;
	mGender = "";
	mEmail = "";
	mWin = mLose = mTie = 0;
	mSymbol = EMPTY;
}
//Player::Player(char symbol, string name)
//{
//	mSymbol = symbol;
//	mName = name;
//	mWin = mLose = mTie = 0;
//}
Player::Player(string name, int age, string gender, string email)
{
	mName = name;
	mAge = age;
	mGender = gender;
	mEmail = email;
	mWin = mLose = mTie = 0;
}

Player::Player(string name, int win, int lose, int tie, int age, string gender, string email)
{
	mName = name;
	mAge = age;
	mWin = win;
	mLose = lose;
	mTie = tie;
	mGender = gender;
	mEmail = email;
}
Player::Player(string name, string passWord, int win, int lose, int tie, int age, string gender, string email)
{
	mName = name;
	mPassWord = passWord;
	mAge = age;
	mWin = win;
	mLose = lose;
	mTie = tie;
	mGender = gender;
	mEmail = email;
}
Player::~Player() {}
//play
void Player::play(vector<char>& caro, int position)
{
	caro[position] = mSymbol;
}
//get
char Player::getSymbol()
{
	return mSymbol;
}
string Player::getName()
{
	return mName;
}

string Player::getPassWord()
{
	return mPassWord;
}

int Player::getAge()
{
	return mAge;
}
string Player::getGender()
{
	return mGender;
}
string Player::getEmail()
{
	return mEmail;
}
int Player::getWin()
{
	return mWin;
}
int Player::getLose()
{
	return mLose;
}
int Player::getTie()
{
	return mTie;
}
string Player::getRate()
{
	double irate = 100 * static_cast<float>(mWin) / (mWin + mLose +mTie);
	string srate = (mWin + mLose + mTie) ? to_string(irate) + "%" : "unknown";
	return srate;
}
//set
void Player::setName(string name)
{
	mName = name;
}
void Player::setPassWord(string passWord)
{
	mPassWord = passWord;
}
void Player::setAge(int age)
{
	mAge = age;
}
void Player::setGender(string gender)
{
	mGender = gender;
}
void Player::setEmail(string email)
{
	mEmail = email;
}
void Player::setSymbol(char symbol)
{
	mSymbol = symbol;
}
void Player::setWin(int win)
{
	mWin = win;
}
void Player::setLose(int lose)
{
	mLose = lose;
}
void Player::setTie(int tie)
{
	mTie = tie;
}
void Player::setRate(string rate)
{
	mRate = rate;
}
//
void Player::increaseWin()
{
	mWin++;
}
void Player::increaseLose()
{
	mLose++;
}
void Player::increaseTie()
{
	mTie++;
}
