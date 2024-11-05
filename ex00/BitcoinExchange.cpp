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
		throw CouldNotOpenException("\tcould not open file database");
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

	if (ifs.rdstate())
		throw CouldNotOpenException("could not open input file");
	std::getline(ifs, str);
	std::getline(ifs, str);
	while (!ifs.eof())
	{
		try
		{
			pipe = str.find(" | ");
			date = str.substr(0, pipe);
			check_date(date);
			if (pipe == -1)
				throw BadInputException("bad use or no use of '|'");
			process_data(date, str.substr(pipe + 3, str.length()));
		}
		catch(BadInputException& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch(TooLargeException& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch(NotPositiveException& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::getline(ifs, str);
	}
}

void			BitcoinExchange::process_data(string date, string val)
{
	check_value(val);

	float					num = static_cast<float>(atof(val.c_str()));
	std::map<string, float>::iterator	it;
	string					auxdate = date;

	if (num > 1000)
		throw TooLargeException("Error: ");
	else if (num < 0)
		throw NotPositiveException("Error: ");

	if (this->data.find(date) == this->data.end())
	{
		this->data[date] = -1;
		it = this->data.find(date);
		it--;
		auxdate = it->first;
		this->data.erase(++it);
	}
	std::cout << date << " => " << num << " = " << num * this->data[auxdate] << std::endl;
}

void			BitcoinExchange::check_date(string date)
{
	if (date.length() != 10)
		throw BadInputException(date);

	int	y = atoi(date.substr(0, 4).c_str());
	int	m = atoi(date.substr(5, 2).c_str());
	int	d = atoi(date.substr(8, 2).c_str());

	for (size_t i = 0; i < date.length(); i++)
	{
		if ((i == 4 || i == 7 || date[i] < '0' || date[i] > '9') && date[i] != '-')
			throw BadInputException(date);
	}
	if (y > 2022 || y < 2009 || m < 1 || m > 12 || d < 1 || d > 31)
		throw BadInputException(date);
}

void			BitcoinExchange::check_value(string val)
{
	int	poinf = 0;
	int	minf = 0;
	for (size_t i = 0; i < val.length(); i++)
	{
		if ((val[i] > '9' || val[i] < '0') && ((val[i] < 9 || val[i] > 13) && val[i] != ' ') && val[i] != '.' && val[i] != '-')
			throw BadInputException(val);
		if (val[i] == '.' || val[i] == '-')
		{
			val[i] == '.' ? poinf++ : minf++;
			if (poinf > 1 || minf > 1)
				throw BadInputException(val);
		}
	}
}

BitcoinExchange::BadInputException::BadInputException(string str) : std::logic_error("Error: bad input => " + str) {}

BitcoinExchange::NotPositiveException::NotPositiveException(string str) : std::out_of_range(str + "not a positive number") {}

BitcoinExchange::TooLargeException::TooLargeException(string str) : std::out_of_range(str + "number too large") {}

BitcoinExchange::CouldNotOpenException::CouldNotOpenException(string str) : std::logic_error("Error: " + str) {}
