#include "UserInput.h"

template<typename T>
T UserInput<T>::input(string msg)
{
	string temp;
	bool valid;
	T result;
	do
	{
		getline(cin, temp);
		valid = ((std::istringstream(temp) >> result >> std::ws).eof()) && !temp.empty();
		if (!valid)
		{
			cout << msg;
		}
	} while (!valid);

	return result;
}

template<>
char UserInput<char>::input(string msg)
{
	string input;
	bool valid;
	do
	{
		getline(cin, input);
		valid = (input.size() == 1) && (isalpha(input[0]));
		if (!valid)
		{
			cout << msg;
		}
	} while (!valid);

	return input[0];
}

template class UserInput<double>;
template class UserInput<int>;