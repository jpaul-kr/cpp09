#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <fstream>

using std::string;

class BitcoinExchange
{
	private:
		std::map<string, float>	data;

	public:
		BitcoinExchange(std::map<string, float> m);
		BitcoinExchange(const BitcoinExchange& cpy);
		~BitcoinExchange();

		BitcoinExchange&	operator=(const BitcoinExchange& cpy);
};

#endif
