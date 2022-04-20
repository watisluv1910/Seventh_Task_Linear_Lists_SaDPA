#include "stack_class.c++"

#include <iostream>
#include <algorithm>
#include <vector>

using std::string;

bool DefinePriority(const char &token);
bool IsLeftAssoc(const char &token);
unsigned CountArgs(const char &token);
bool IsOperator(const char &token);
bool IsFunction(const char &token);
bool IsIdentificator(const char &token);
void ExpandString(string &expression);
bool ShuntingYard(string &in_expression, string &out_expression);

int main()
{
	string in_expression, out_expression;
	std::cin >> in_expression;


	if (ShuntingYard(in_expression, out_expression))
	{
		std::cout << '\n' << out_expression << '\n';
	}
	
	return 0;
}

bool DefinePriority(const char &token)
{
	switch (token)
	{
	case '!':
		return 4;

	case '*':
	case '/':
	case '%':
		return 3;

	case '+':
	case '-':
		return 2;

	case '=':
		return 1;
	}
	return 0;
}

bool IsLeftAssoc(const char &token)
{
	switch (token)
	{
	case '*':
	case '/':
	case '%':
	case '+':
	case '-':
	case '=':
		return true;

	case '!':
		return false;
	}
	return false;
}

unsigned CountArgs(const char &token)
{
	switch (token)
	{
	case '*':
	case '/':
	case '%':
	case '+':
	case '-':
	case '=':
		return 2;

	case '!':
		return 1;

	default:
		return token - 'A';
	}
	return 0;
}

bool IsOperator(const char &token)
{
	string operators = "+-*/!%=";
	if (operators.find(token) != string::npos)
	{
		return true;
	}
	return false;
}

bool IsFunction(const char &token)
{
	return (token >= 'A' && token <= 'Z');
}

bool IsIdentificator(char &token)
{
	return (token >= '0' && token <= '9' || token >= 'a' && token <= 'z');
}

void ExpandString(string& expression)
{
	for (size_t i = 0; i < expression.size(); i++)
	{
		if (expression.at(i) == '(')
		{
			expression.at(i) = ')';
		}
		else if (expression.at(i) == ')')
		{
			expression.at(i) = '(';
		}
		else
		{
			continue;
		}
	}
	for (size_t i = 0; i < expression.size() / 2; i++)
	{
		std::swap(expression.at(i), expression.at(expression.size() - i - 1));
	}
}

bool ShuntingYard(string &in_expression, string &out_expression)
{
	ExpandString(in_expression);

	std::cout << in_expression << '\n';

	Stack<char> stack;

	for (auto &token : in_expression)
	{
		std::cout << '\n' << token;
		if (token != ' ')
		{
			if (IsIdentificator(token))
			{
				out_expression += token;
			}
			else if (IsFunction(token))
			{
				stack.Push(token);
			}
			else if (token == ',')
			{
				bool par_ex = false; // parenthesis_exsistance
				while (stack.get_size())
				{
					char temp_token = stack.Top();
					if (temp_token == '(')
					{
						par_ex = true;
						break;
					}
					else
					{
						out_expression += temp_token;
						stack.Pop();
					}
				}
				if (!par_ex)
				{
					std::cerr << "\nError _ 1 _ separator or parentheses mismatched\n";
					return false;
				}
			}
			else if (IsOperator(token))
			{
				while (stack.get_size())
				{
					char temp_token = stack.Top();

					if (IsOperator(temp_token) 
						&& (IsLeftAssoc(token) 
							&& (DefinePriority(token) <= DefinePriority(temp_token))
						|| !IsLeftAssoc(token) 
							&& (DefinePriority(token) < DefinePriority(temp_token))))
					{
						out_expression += temp_token;
						stack.Pop();
					}
					else
					{
						break;
					}
				}
				stack.Push(token);
			}
			else if (token == '(')
			{
				stack.Push(token);
			}
			else if (token == ')')
			{
				bool par_ex = false; // parenthesis_exsistance
				while (stack.get_size())
				{
					char temp_token = stack.Top();
					if (temp_token == '(')
					{
						par_ex = true;
						break;
					}
					else
					{
						out_expression += temp_token;
						stack.Pop();
					}
				}
				if (!par_ex)
				{
					std::cerr << "\nError _ 2 _ parentheses mismatched\n";
					return false;
				}
				stack.Pop();
				if (stack.get_size())
				{
					char temp_token = stack.Top();
					if (IsFunction(temp_token))
					{
						out_expression += temp_token;
						stack.Pop();
					}
				}
			}
			else
			{
				std::cerr << "\nError _ 3 _ unknown token\n";
				return false; // unknown token
			}
		}
	}
	while (stack.get_size())
	{
		char temp_token = stack.Top();
		if (temp_token == '(' || temp_token == ')')
		{
			std::cerr << "\nError _ 4 _ parentheses mismatched\n";
			return false;
		}
		out_expression += temp_token;
		stack.Pop();
	}

	ExpandString(out_expression);

	return true;
}

//void OutputMenu(const string& expression)
//{
//
//}