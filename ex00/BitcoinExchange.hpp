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

		class	BadInputException : public std::logic_error
		{
			public:
				BadInputException(string str);
		};

		class	NotPositiveException : public std::out_of_range
		{
			public:
				NotPositiveException(string str);
		};

		class	TooLargeException : public std::out_of_range
		{
			public:
				TooLargeException(string str);
		};

		class	CouldNotOpenException : public std::logic_error
		{
			public:
				CouldNotOpenException(string str);
		};
};

#endif
