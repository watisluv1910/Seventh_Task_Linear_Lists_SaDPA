#include "stack_class.h"

#include <algorithm>
#include <iostream>

template <typename T>
void Stack<T>::Push(T data)
{
	ResizeStack(size_ + 1);
	data_[size_ - 1] = data;
}

template<typename T>
void Stack<T>::Print()
{
	for (size_t i = 0; i < this->size; i++)
	{
		std::cout.width(5);
		std::cout << (this->data_)[i];
	}
}

template<typename T>
void Stack<T>::Pop()
{
	ResizeStack(size_ - 1);
}

template<typename T>
T Stack<T>::Top()
{
	return data_[size_ - 1];
}

template<typename T>
bool Stack<T>::Empty()
{
	return !size_;
}

template<typename T>
void Stack<T>::Clear()
{
	delete[] data_;
	this->size_ = 0;
	data_ = new T[size_];
}

template<typename T>
void Stack<T>::ResizeStack(size_t new_size)
{
	T* temp_stack = new T[new_size];

	memcpy(temp_stack, data_, sizeof(T) * ((size_ <= new_size) ? size_ : new_size));

	delete[] data_;
	data_ = temp_stack;

	size_ = new_size;
}
