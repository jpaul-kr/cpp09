#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& cpy) :  st(cpy.st) {}

RPN::~RPN() {}

RPN&	RPN::operator=(const RPN& cpy)
{
	this->st = cpy.st;
}

void	RPN::addArguments(string arg)
{
	for (int i = 0; i < arg.length(); i++)
	{
		if (is_digit(arg[i]) || arg[i] == '+' || arg[i] == '-' || arg[i] == '/' || arg[i] == '*')
		{
			if (is_digit(arg[i]) && is_digit(arg[i + 1]))
				throw ErrorException();
			this->deque.push_back(arg[i] - '0');
		}
		else if (arg[i] != ' ')
			throw ErrorException();
	}
}

RPN::ErrorException::ErrorException() : std::logic_error("\tError\n") {}
