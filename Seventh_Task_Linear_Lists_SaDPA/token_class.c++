#include "token_class.h"

#include <iostream>

using std::string;

template<typename T>
Token<T>::Token(T value) : value_(value)
{
	set_priority();
	set_args_number();
	set_left_assoc();
	set_state();
}

template<typename T>
void Token<T>::set_priority()
{
	switch (value_)
	{
	case '!':
	case '^':
		priority_ = 4;
		break;

	case '*':
	case '/':
	case '%':
		priority_ = 3;
		break;

	case '+':
	case '-':
		priority_ = 2;
		break;

	case '=':
		priority_ = 1;
		break;
	}
}

template<typename T>
void Token<T>::set_args_number()
{
	switch (value_)
	{
	case '*':
	case '/':
	case '%':
	case '+':
	case '-':
	case '=':
	case '^':
		args_number_ = 2;
		break;

	case '!':
		args_number_ = 1;
		break;
	}
}

template<typename T>
void Token<T>::set_left_assoc()
{
	switch (value_)
	{
	case '*':
	case '/':
	case '%':
	case '+':
	case '-':
	case '=':
	case '^':
		is_left_assoc_ = true;
		break;
	}
}

template<typename T>
void Token<T>::set_state()
{
	if (value_ >= 'A' && value_ <= 'Z')
	{
		is_function_ = true;
	}
	else if (value_ >= '0' && value_ <= '9' || value_ >= 'a' && value_ <= 'z')
	{
		is_identificator_ = true;
	}
	else
	{
		string operators_list = "+-*^/!%=";
		if (operators_list.find(value_) != string::npos)
		{
			is_operator_ = true;
		}
	}
}
