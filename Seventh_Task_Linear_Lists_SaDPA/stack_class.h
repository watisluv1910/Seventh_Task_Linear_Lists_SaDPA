#ifndef STACK_CLASS_H
#define STACK_CLASS_H

#include "token_class.h"
#include "token_class.c++"

template <typename T>
class Stack
{
public:

	// Makes default initialization
	Stack() : size_(0ull), data_list_(new Token<T>*[size_]) {};

	// Adds a new token to the end of the stack
	void Push(Token<T>* data = T*());

	// Removes and returns the top element of the stack
	Token<T>* Pop();

	// Returns the top element of the stack
	Token<T>* Top();

	// Clears the stack data_list
	void Clear();

	// Checks the emptiness of the stack
	bool Empty();

	size_t get_size() { return size_; };
private:

	size_t size_;
	Token<T>** data_list_; // List of tokens pointers

	// Changes the stack size
	void ResizeStack(size_t new_size = size_);
};

#endif // !STACK_CLASS_H
