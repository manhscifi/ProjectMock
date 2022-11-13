#pragma once
#include<iostream>
#include<vector>
#include<string>
#include"Macro.h"
using namespace std;

class Player
{
private:
	string mName;
	string mPassWord;
	int mAge;
	string mGender;
	string mEmail;
	int mWin, mLose, mTie;
	string mRate;
	char mSymbol;
public:
	Player();
	Player(string name, int age, string gender, string email);
	Player(string name, int win, int lose, int tie, int age, string gender, string email);
	Player(string name, string passWord, int win, int lose, int tie, int age, string gender, string email);
	~Player();
	//play
	void play(vector<char>& caro, int position);
	//get
	string getName();
	string getPassWord();
	int getAge();
	string getGender();
	string getEmail();
	char getSymbol();
	int getWin();
	int getLose();
	int getTie();
	string getRate();
	//set
	void setAge(int age);
	void setPassWord(string passWord);
	void setGender(string gender);
	void setEmail(string email);
	void setName(string name);
	void setSymbol(char symbol);
	void setWin(int win);
	void setLose(int lose);
	void setTie(int tie);
	void setRate(string rate);
	//
	void increaseWin();
	void increaseLose();
	void increaseTie();
};

