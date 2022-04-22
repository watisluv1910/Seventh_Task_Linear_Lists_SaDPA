#include "stack_class.h"
#include "stack_class.c++"

#include <iostream>
#include <algorithm>

using std::string;

void ReverseString(string &expression);
template <typename T>
bool FindBracket(Stack<T>& stack, string& out_expression);
template <typename T>
bool CalculateLogicalExpression(Token<T>*& token, Token<T>*& top_token);
bool ShuntingYard(string &in_expression, string &out_expression);
inline void OutputMenu();

int main()
{
	OutputMenu();

	std::cout << "Your choise is:\n";

	unsigned path = 0; // Menu navigation variable
	std::cin >> path;

	// cin.clear and cin.ignore are used to prevent fake input:
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');

	string in_expression = ""; // Original expression
	string out_expression = ""; // Converted expression

	while (path)
	{
		switch (path)
		{
		case 1:

			// Original expression string purification:
			in_expression.clear();

			std::cout << "\nEnter the new infix form expression:\n";

			std::cin >> in_expression;

			// cin.clear and cin.ignore are used to prevent fake input:
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			break;
		case 2:

			if (!in_expression.size())
			{
				// If the original expression wasn't entered yet:
				std::cerr << "\nError (1): An infix expression " // Error 1
					<< "wasn't entered yet.\n";
			}
			else
			{
				// Main converting algorithm call:
				if (ShuntingYard(in_expression, out_expression))
				{
					std::cout << "\nYour postfix form expression is:\n"
						<< out_expression << '\n';
				}
				// Converted expression string purification:
				out_expression.clear();
			}
			break;
		default:

			std::cerr << "\nError (0): Wrong path entered.\n"; // Error 0
			break;
		}

		system("pause");
		system("cls"); // clear screen

		OutputMenu();

		if (in_expression.size()) // If the original expression was entered:
		{	
			std::cout << "Your current infix form expression is:\n"
				<< in_expression << '\n';
		}

		// Next menu navigation step:
		std::cout << "\nYour choise is:\n";
		std::cin >> path;

		// cin.clear and cin.ignore are used to prevent fake input
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');		
	}
	return 0;
}

void ReverseString(string &expression)
{
	// Brackets rearrangement is required ro correctly display reversed string:
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
	// The loop goes to the middle of the string:
	for (size_t i = 0; i < expression.size() / 2; i++)
	{
		// Permutation of the current and its opposite element:
		std::swap(expression.at(i), expression.at(expression.size() - i - 1));
	}
}

// The algorithm adds stack content to the 
// converted string untill the left bracket arrives
template <typename T>
bool FindBracket(Stack<T> &stack, string& out_expression)
{
	// In general adds the expression inside the brackets to the out_expression

	bool bracket_ex = false; // Defines bracket exsistance
	while (!stack.Empty())
	{
		Token<char>* top_token = stack.Top();

		if (top_token->get_value() == '(')
		{
			bracket_ex = true;
			break;
		}
		else
		{
			// Removing the last token from the stack and 
			// adding it to the converted string:
			out_expression += stack.Pop()->get_value();
		}
	}
	return bracket_ex; 
}

// The alorithm calculates logical expression in simplified form
template <typename T>
bool CalculateLogicalExpression(Token<T>* &token, Token<T>* &top_token) 
{
	// While at the top of the stack there is a top_token operator, 
	// as well as the token operator is left-associative AND its priority 
	// less OR the same than that of the top_token operator, OR 
	// the token operator is right-associative AND 
	// its priority is less than that of the top_token operator

	const bool a = top_token->get_op_state(); // top_token is an operator
	const bool b = top_token->get_left_assoc(); // top_token is left associative
	const unsigned c = top_token->get_priority(); // top_token priority
	const bool d = token->get_left_assoc(); // token is left associative
	const unsigned e = token->get_priority(); // token priority

	return a && (b && (e <= c) || !d && (e < c));
}

// The algorithm processes an infix expression left-to-right
// and generates the corresponding RPN (postfix) expression
bool ShuntingYard(string &in_expression, string &out_expression)
{
	// This algorithm is a variation of Dijkstra's "Shunting yard" algorithm

	Stack<char> stack; // Stack of tokens (Token class objects) pointers

	// Iteration over each symbol of the original expression: 

	for (auto &in_element : in_expression)
	{	
		// Pointer at current token object
		Token<char>* token = new Token<char>(in_element);

		if (token->get_value() != ' ') // Passing space symbols
		{
			if (token->get_ident_state())
			{
				// Adding the current token to the
				// converted expression:
				out_expression += token->get_value();
			}
			else if (token->get_func_state())
			{
				stack.Push(token);
			}
			// If token is a separator of func arguments:
			else if (token->get_value() == ',')
			{
				if (!FindBracket(stack, out_expression))
				{
					std::cerr << "\nError (2): Separator or " // Error 2
						<< "bracket mismatched.\n";
					return false;
				}
			}
			else if (token->get_op_state())
			{
				while (!stack.Empty())
				{
					Token<char>* top_token = stack.Top();

					if (CalculateLogicalExpression(token, top_token))
					{
						// Removing the last token from the stack and 
						// adding it to the converted string:
						out_expression += stack.Pop()->get_value();
					}
					else
					{
						break;
					}
				}
				stack.Push(token);
			}
			else if (token->get_value() == '(')
			{
				stack.Push(token);
			}
			else if (token->get_value() == ')')
			{
				if (!FindBracket(stack, out_expression))
				{
					std::cerr << "\nError (3): Bracket mismatched.\n"; // Error 3
					return false;
				}
				stack.Pop();
				if (!stack.Empty())
				{
					Token<char>* top_token = stack.Top();
					if (top_token->get_func_state())
					{
						// Removing top_token from the stack and 
						// adding it to the converted string:
						out_expression += stack.Pop()->get_value();
					}
				}
			}
			else
			{
				std::cerr << "\nError (4): Unknown token.\n"; // Error 4
				return false;
			}
		}
	}
	while (!stack.Empty())
	{
		Token<char>* token = stack.Pop();

		if (token->get_value() == '(' || token->get_value() == ')')
		{
			std::cerr << "\nError (5): Bracket mismatched.\n"; // Error 5
			return false;
		}
		// Removing the last token from the stack and 
		// adding it to the converted string:
		out_expression += token->get_value();
	}

	return true;
}

inline void OutputMenu()
{
	std::cout << "Practical task num.7\nIKBO-03-21 Nasevich V.V.\n"
		"Variant num. 19.\n\nMenu:\n"
		"1)Enter <1> to enter the new expression.\n"
		"2)Enter <2> to print the expression in postfix form (polish notation).\n"
		"3)Enter <0> to end the programm.\n\n";
}
