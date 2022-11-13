#pragma once
#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<windows.h>
#include"UserInput/UserInput.h"
#include"Macro.h"
using namespace std;

class IO
{
public:
	//input
	static string inputName();
	static string inputPassWord();
	static int inputAge();
	static string inputGender();
	static string inputEmail();
	static int inputPosition();
	//output
	static void printCaro(const vector<char>& caro, const string& title);
	static void printPlayer(string name, string rate, int numOfWin, int numOfLose, int numOfTie);
	//color
	static void colorize(string str, int color);
};

