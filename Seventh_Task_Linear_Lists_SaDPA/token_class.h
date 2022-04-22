#ifndef TOKEN_CLASS_H
#define TOKEN_CLASS_H

template <typename T>
class Token
{
public:

	Token(T value = T());

	T get_value() { return value_; };

	// Returns the operator priority
	unsigned get_priority() { return priority_; };

	// Returns the number of arguments that is necessary for
	// operator to work correctly
	unsigned get_args_number() { return args_number_; };

	// Returns the associativity of an operator  
	// (property that determines how operators of the same priority
	// are grouped in the absence of brackets)
	bool get_left_assoc() { return is_left_assoc_; };

	// Returns the value the statement that the token is an operator
	bool get_op_state() { return is_operator_; };

	// Returns the value the statement that the token is a function
	bool get_func_state() { return is_function_; };

	// Returns the value the statement that the token is an identificator
	bool get_ident_state() { return is_identificator_; };
private:

	T value_;

	unsigned priority_ = 0U, 
		args_number_ = 0U; 

	bool is_left_assoc_ = false, //
		is_operator_ = false, //
		is_function_ = false, //
		is_identificator_ = false; //

	void set_priority();
	void set_args_number();
	void set_left_assoc();
	void set_state();
};

#endif // !TOKEN_CLASS_H
