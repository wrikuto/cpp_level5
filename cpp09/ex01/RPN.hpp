#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>
# include <stdexcept>

class RPN
{
private:
	std::stack<int> _stack;
	bool is_operator(const std::string &token);
	void apply_operator(const std::string &token);


public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();
	void calculate(const std::string &expression);
};

#endif