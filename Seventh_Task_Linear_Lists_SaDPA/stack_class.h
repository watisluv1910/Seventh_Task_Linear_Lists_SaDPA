#ifndef STACK_CLASS_H
#define STACK_CLASS_H

template <typename T>
class Stack
{
public:

	Stack() : size_(0ull), data_(new T[size_]) {};

	void Push(T data = T());
	void Print();

	void Pop();
	T Top();

	void Clear();
	bool Empty();

	size_t get_size() { return size_; };
private:

	size_t size_;
	T* data_;
	void ResizeStack(size_t new_size = size_);
};

#endif // !STACK_CLASS_H
