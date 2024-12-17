#include  "BitcoinExchange.hpp"

int	main(int  argc, char **argv)
{
	BitcoinExchange	b;

	try
	{
		if (argc != 2)
			throw BitcoinExchange::CouldNotOpenException("bad input arguments");
		b.addData("database/data.csv");
		b.process_input(argv[1]);
	}
	catch(BitcoinExchange::CouldNotOpenException& e)
	{
		std::cout << e.what() << std::endl; 
	}
}
