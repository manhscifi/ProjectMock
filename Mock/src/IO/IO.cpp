#include "IO.h"

//input
string IO::inputName()
{
	string name;
	bool valid;
	cout << "\tType name: ";
	do
	{
		getline(cin, name);
		valid = !name.empty();
		if (!valid)
		{
			cout << "\tInvalid name.Type again : ";
		}
	} while (!valid);
	return name;
}
int IO::inputAge() 
{
	int age;
	bool valid;
	cout << "\tType age: ";
	do
	{
		age = UserInput<int>::input();
		valid = (age <= 100 && age >= 1);
		if (!valid)
		{
			cout << "\tReally.\n";
		}
	} while (!valid);
	return age;
}
string  IO::inputGender()
{
	string gender;
	bool valid;
	cout << "\tType gender: ";
	do
	{
		getline(cin, gender);
		valid = !gender.empty();
		if (!valid)
		{
			cout << "\tType again : ";
		}
	} while (!valid);
	return gender;
}
string  IO::inputEmail()
{
	string email;
	bool valid;
	cout << "\tType email: ";
	do
	{
		getline(cin, email);
		valid = !email.empty();
		if (!valid)
		{
			cout << "\tType again : ";
		}
	} while (!valid);
	return email;
}
char IO::inputSymbol()
{
	string symbol;
	bool valid;
	cout << "\tChoose X or O: ";
	do
	{
		getline(cin, symbol);
		valid = symbol.size() == 1 && toupper(symbol[0]) == symbolX || toupper(symbol[0]) == symbolO;
		if (!valid)
		{
			cout << "\tInvalid. Type again: ";
		}
	} while (!valid);
	return symbol[0];
}
int IO::inputPosition()
{
	int x, y;
	bool valid;
	//cout << "Type position: ";
	do
	{
		x = UserInput<int>::input();
		y = UserInput<int>::input();
		valid = (x <= SIZE && x >= 1) && (y <= SIZE && y >= 1);
		if (!valid)
		{
			cout << "Out of range.\n";
		}
	} while (!valid);

	return (x - 1) * SIZE + (y - 1);
}
//output
void IO::printCaro(const vector<char>& caro, const string& title)
{
	cout << title << endl;
	cout << setfill('-');
	cout << setw(W) << "-" << endl;
	for (int col = 1; col <= SIZE; col++)
	{
		for (int row = 1; row <= SIZE; row++)
		{
			cout << "| ";
			if (caro[(col - 1) * SIZE + (row - 1)] == symbolX)
			{
				colorize(string(1, caro[(col - 1) * SIZE + (row - 1)]), RED);
			}
			else
			{
				colorize(string(1, caro[(col - 1) * SIZE + (row - 1)]), BLUE);
			}			
			cout<< " ";
		}
		cout << "|\n";
		cout << setw(W) << "-" << endl;
	}
}
void IO::printPlayer(string name, string rate, int numOfWin, int numOfLose, int numOfTie)
{	
	cout << "Player name: " << name << endl;
	cout << "- Rate: " << rate << endl;
	cout << "- Win: " << numOfWin << endl;
	cout << "- Lose: " << numOfLose << endl;
	cout << "- Tie: " << numOfTie << endl;
	cout << "\n";
}
void IO::colorize(string str, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << str;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT);
}