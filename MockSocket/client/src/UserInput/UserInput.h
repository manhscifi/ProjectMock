#pragma once
#include<iostream>
#include<sstream>
using namespace std;

template<typename T>
class UserInput
{
public:

	static T input(string msg = "Enter again: ");
};
