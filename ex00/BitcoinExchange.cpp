#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::map<string, float>& map) : data(map) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& cpy) : data(cpy.data) {}

BitcoinExchange::~BitcoinExchange() {}

void	BitcoinExchange::addData(const string file)
{
	std::ifstream	ifs(file.c_str());
	string		str;

	if (ifs.rdstate())
		throw std::logic_error("\terror with file database");
	std::getline(ifs, str);

	while (!ifs.eof())
	{
		std::getline(ifs, str);
		add_to_map(str);
	}
}

void	BitcoinExchange::add_to_map(const string str)
{
	string	key;
	float	value;

	key = str.substr(0, str.find(",") + 1);
	value = static_cast<float>(str.substr(str.find(","), str.length()));
}
