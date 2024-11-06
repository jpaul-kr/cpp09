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
	this->deque = cpy.deque;
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
			this->deque.push_back(arg[i]);
		}
		else if (arg[i] != ' ' && (arg[i] > 13 || arg[i] < 9))
			throw ErrorException();
	}
	/*for (size_t i = 0; i < this->deque.size(); i++)
	{
		std::cout << this->deque[i] << std::endl;
	}*/
}

void	RPN::rpn_calculate()
{
	char in_line = '\0';

	for (size_t i = 0; i < this->deque.size(); i++)
	{
		if (isdigit(this->deque[i]))
			this->stack.push(this->deque[i] - '0');
		operate(this->deque[i], in_line);
		if (this->stack.size() > 2)
			throw ErrorException();
	}
	if (this->stack.size() > 1)
		throw ErrorException();
	std::cout << "result: " << this->stack.top() << std::endl;
}

void	RPN::operate(char oper, char& in_line)
{
	if (in_line)
		throw ErrorException();
	if (this->stack.size() < 2)
	{
		in_line = oper;
		return ;
	}

	int	num1 = this->stack.top();
	this->stack.pop();

	int	num2 = this->stack.top();
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
	in_line = '\0';
}

RPN::ErrorException::ErrorException() : std::logic_error("\tError") {}
