#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &src)
{
    this->_stack = src._stack;
}

RPN &RPN::operator=(const RPN &src)
{
    if (this != &src)
        this->_stack = src._stack;
    return (*this);
}

RPN::~RPN() {}


bool RPN::is_operator(const std::string &token)
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

void RPN::apply_operator(const std::string &token)
{
    if (_stack.size() < 2)
        throw std::runtime_error("error: not enough operands"); // "xot"を"not"に修正

    int b = _stack.top();
    _stack.pop();
    int a = _stack.top();
    _stack.pop();

    if (token == "+")
        _stack.push(a + b);
    else if (token == "-")
        _stack.push(a - b);
    else if (token == "*")
        _stack.push(a * b);
    else if (token == "/")
    {
        if (b == 0)
            throw std::runtime_error("error: zero division is not possible.");
        _stack.push(a / b);
    }
}

void RPN::calculate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (isdigit(token[0]) && token.length() == 1)
            _stack.push(token[0] - '0');
        else if (isdigit(token[0]))
            throw std::runtime_error("error: Numbers must be less than 10");
        else if (is_operator(token))
            apply_operator(token);
        else
            throw std::runtime_error("error: Invalid token");
    }

    if (_stack.size() != 1)
        throw std::runtime_error("error: Invalid expression");

    std::cout << _stack.top() << std::endl;
}