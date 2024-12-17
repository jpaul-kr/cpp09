#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& cpy) 
{
	*this = cpy;
}

RPN::~RPN() {}

RPN&	RPN::operator=(const RPN& cpy)
{
	this->stack = cpy.stack;
	this->list = cpy.list;
	return *this;
}

void	RPN::addArguments(string arg)
{
	for (size_t i = 0; i < arg.length(); i++)
	{
		if (isdigit(arg[i]) || arg[i] == '+' || arg[i] == '-' || arg[i] == '/' || arg[i] == '*')
		{
			if (isdigit(arg[i]) && isdigit(arg[i + 1]))
				throw ErrorException();
			this->list.push_back(arg[i]);
		}
		else if (arg[i] != ' ' && (arg[i] > 13 || arg[i] < 9))
			throw ErrorException();
	}
}

void	RPN::rpn_calculate()
{
	std::list<char>::iterator	it;

	for (it = this->list.begin(); it != this->list.end(); it++)
	{
		if (isdigit(*it))
			this->stack.push(*it - '0');
		else
			operate(*it);
	}
	if (this->stack.size() > 1)
		throw ErrorException();
	std::cout << "result: " << this->stack.top() << std::endl;
}

void	RPN::operate(char oper)
{
	if (this->stack.size() < 2)
		throw ErrorException();

	float	num1 = this->stack.top();
	this->stack.pop();

	float	num2 = this->stack.top();
	this->stack.pop();
	switch (oper)
	{
		case '*':
			this->stack.push(num2 * num1);
			break ;
		case '/':
			this->stack.push(num2 / num1);
			break ;
		case '+':
			this->stack.push(num2 + num1);
			break ;
		case '-':
			this->stack.push(num2 - num1);
			break ;
		default:
			break ;
	}
}

RPN::ErrorException::ErrorException() : std::logic_error("\tError") {}
