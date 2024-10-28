#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::map<string, float> map) 
{
	this->data = map;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& cpy) : data(cpy.data) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& cpy)
{
	this->data = cpy.data;
	return *this;
}

void			BitcoinExchange::addData(const string file)
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

void			BitcoinExchange::add_to_map(const string str)
{
	string	key;
	float	value;

	key = str.substr(0, str.find(","));
	value = static_cast<float>(atof(str.substr(str.find(",") + 1, str.length()).c_str()));

	this->data[key] = value;
}

void			BitcoinExchange::print_data()
{
	std::cout << std::fixed << std::setprecision(2) << this->data["2013-06-17"] << std::endl;
}
