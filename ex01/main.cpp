#include "RPN.hpp"

int	main(int argc, char** argv)
{
	try
	{
		if (argc != 2)
			throw RPN::ErrorException();
		RPN	rpn;

		rpn.addArguments(argv[1]);
		rpn.rpn_calculate();
	}
	catch (RPN::ErrorException& e)
	{
		std::cout << e.what() << std::endl;
	}
}
