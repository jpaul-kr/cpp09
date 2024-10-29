#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <fstream>
# include <map>
# include <cstdlib>
# include <iomanip>

using std::string;

class BitcoinExchange
{
	private:
		std::map<string, float>	data;

	public:
		BitcoinExchange();
		BitcoinExchange(std::map<string, float> m);
		BitcoinExchange(const BitcoinExchange& cpy);
		~BitcoinExchange();

		BitcoinExchange&	operator=(const BitcoinExchange& cpy);
		void			addData(const string file);
		void			add_to_map(const string str);
		void			print_data();
		void			check_date(string date);
		void			process_data(string date, string val);
		void			process_input(string input);

		class	BadInputException : std::invalid_argument
		{
			BadInputException(string date);
		};

		class	NotPositiveException : std::out_of_range
		{
			NotPositiveException("Error: ");
		};

		class	TooLargeException : std::out_of_range
		{
			TooLargeException("Error: ");
		};

		class	CouldNotOpenException : std::logic_error
		{
			CouldNotOpenException(string str);
		};
};

#endif
