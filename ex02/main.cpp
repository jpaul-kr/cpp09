#include "PmergeMe.hpp"

int	main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	PmergeMe	merge(&argv[1]);

	merge.print_lst();
	merge.print_vec();
}
