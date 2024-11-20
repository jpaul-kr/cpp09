#include "PmergeMe.hpp"

int	main(int argc, char** argv)
{
	try
	{
		if (argc < 2)
			throw PmergeMe::errorException();

		PmergeMe		merge(&argv[1]);

		merge.merge_process();
		merge.print_time();
	}
	catch (PmergeMe::errorException&	e)
	{
		std::cout << e.what() << std::endl;
	}
}
