#include "RPN.hpp"

int	main(int argc, char** argv)
{
	if (argc != 2)
		throw ErrorException::ErrorException();
	RPN	rpn;

	rpn.addAArguments(argv[1]);
}
