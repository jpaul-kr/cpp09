#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
# include <stack>
# include <cctype>

using std::string;

class	RPN
{
	private:
		std::stack<float>		stack;
		std::deque<char>	deque;
	
	public:
		RPN();
		RPN(const RPN& cpy);
		~RPN();

		RPN&	operator=(const RPN& cpy);
		void	addArguments(string arg);
		void	rpn_calculate();
		void	operate(char oper);

		class	ErrorException : public std::logic_error
		{
			public:
				ErrorException();
		};
};

#endif
