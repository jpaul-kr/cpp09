#include  "BitcoinExchange.hpp"

int	main(int  argc, char **argv)
{
	if (argc != 2)
		return 1;
	BitcoinExchange	b;

	try
	{
		b.addData("cpp_09/data.csv");
		b.process_input(argv[1]);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl; 
	}
}
