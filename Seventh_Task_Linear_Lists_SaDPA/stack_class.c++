#include "stack_class.h"

#include <iostream>
#include <algorithm>

template <typename T>
void Stack<T>::Push(Token<T>* data)
{
	ResizeStack(size_ + 1);
	data_list_[size_ - 1] = data;
}

template<typename T>
Token<T>* Stack<T>::Pop()
{
	Token<T>* temp_token = Top();
	ResizeStack(size_ - 1);
	return temp_token;
}

template<typename T>
Token<T>* Stack<T>::Top()
{
	return  data_list_[size_ - 1];
}

template<typename T>
bool Stack<T>::Empty()
{
	return !size_;
}

template<typename T>
void Stack<T>::Clear()
{
	delete[] data_list_;
	this->size_ = 0;
	data_list_ = new Token<T>*[size_];
}

template<typename T>
void Stack<T>::ResizeStack(size_t new_size)
{
	Token<T>** temp_stack = new Token<T>*[new_size];

	memcpy(temp_stack, data_list_, sizeof(Token<T>*)
		* ((size_ <= new_size) ? size_ : new_size));

	delete[] data_list_;
	data_list_ = temp_stack;

	size_ = new_size;
}
