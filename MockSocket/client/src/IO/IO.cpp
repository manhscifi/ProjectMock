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
string IO::inputPassWord()
{
	string password;
	cout << "\tType password: ";
	getline(cin, password);
	while (password.size() < 3 || password.size() > 10)
	{
		cout << "Your password length must be 3-10: ";
		getline(cin, password);
	}
	return password;
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
string IO::inputGender()
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
string IO::inputEmail()
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
int IO::inputPosition()
{
	int x, y;
	bool valid;
	//cout << "Type position: ";
	do
	{
		x = UserInput<int>::input();
		y = UserInput<int>::input();
		valid = (x <= TABLE_SIZE && x >= 1) && (y <= TABLE_SIZE && y >= 1);
		if (!valid)
		{
			cout << "Out of range.\n";
		}
	} while (!valid);

	return (x - 1) * TABLE_SIZE + (y - 1);
}
//output
void IO::printCaro(const vector<char>& caro, const string& title)
{
	cout << title << endl;
	cout << setfill('-');
	cout << setw(ALIGN) << "-" << endl;
	for (int col = 1; col <= TABLE_SIZE; col++)
	{
		for (int row = 1; row <= TABLE_SIZE; row++)
		{
			cout << "| ";
			if (caro[(col - 1) * TABLE_SIZE + (row - 1)] == symbolX)
			{
				colorize(string(1, caro[(col - 1) * TABLE_SIZE + (row - 1)]), RED);
			}
			else
			{
				colorize(string(1, caro[(col - 1) * TABLE_SIZE + (row - 1)]), BLUE);
			}			
			cout<< " ";
		}
		cout << "|\n";
		cout << setw(ALIGN) << "-" << endl;
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
void IO::pause()
{
	cout << "Press any key to return menu.\n";
	cin.ignore(100000, '\n');
}