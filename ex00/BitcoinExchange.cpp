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

void			BitcoinExchange::process_input(string input)
{
	std::ifstream	ifs(input.c_str());
	string		str;
	string		date;
	int		pipe;

	std::getline(ifs, str);
	while (!ifs.eof())
	{
		std::getline(ifs, str);
		pipe = str.find(" | ");
		if (pipe == -1)
			throw BadInputException("| missing");
		date = str.substr(0, pipe);
		check_date(date);
		process_data(date, str.substr(pipe + 1, str.length()));
	}
}

void			BitcoinExchange::process_data() // si la key existe: calcular y sacar resultado, 
{							// sino primero crear nueva key y usar find para pillar el iter y hacer iter--;
}

void			BitcoinExchange::check_date(string date)
{
	int	y = atoi(date.substr(0, 4));
	int	m = atoi(date.substr(5, 2));
	int	d = atoi(date.substr(8, 2));

	for (int i = 0; i < date.length(); i++)
	{
		if (((i == 4 || i == 7) && date[i] != '-') || (date[i] < '0' || date[i] > '9'))
			throw BadInputException(date);
	}
	if (y > 2022 || y < 2009 || m < 1 || m > 12 || d < 1 || d > 31)
		throw BadInputException(date);
}

BitcoinExchange::BadInputException::BadInputException(string str) : std::invalid_argument("Error: bad input => " + str) {}

BitcoinExchange::NotPositiveException::NotPositiveException(string str) : std::out_of_range(str + "not a positive number") {}

BitcoinExchange::TooLargeException::TooLargeException(string str) : std::out_of_range(str + "number too large") {}

BitcoinExchange::CouldNotOpenException::CouldNotOpenException(string str) : std::logic_error("Error: " + str) {}
