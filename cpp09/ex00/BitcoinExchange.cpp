#include "BitcoinExchange.hpp"

static std::string& trim(std::string& s)
{
	s.erase(0, s.find_first_not_of(" \t\n"));
	s.erase(s.find_last_not_of(" \t\n") + 1);
	return (s);
}

BitcoinExchange::BitcoinExchange()
{
	std::string		line;
	std::ifstream	file("data.csv");
	size_t			point;
	std::string 	date;
	double 			value;

	if (!file.is_open())
	{
		std::cerr << "error: can't open the file." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::getline(file, line);
	while(std::getline(file, line))
	{
		point = line.find(',');
		if (point == std::string::npos)
		{
			std::cerr << "error: invalid paramter" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		date = line.substr(0, point);
		try
		{
			value = std::stod(line.substr(point + 1));
		} 
		catch (...)
		{
			std::cerr << "error: can't parse value" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		this->get_data(date, value);
	}
	file.close();
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &src)
{
	if (this != &src)
		this->_data = src._data;
	return (*this);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src)
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::get_data(std::string date, float value)
{
	this->_data.insert(std::make_pair(date, value));
}

std::map<std::string, float> BitcoinExchange::get_data()
{
	return (this->_data);
}


std::vector<std::string> BitcoinExchange::split(std::string str, char delimiter)
{
	std::vector<std::string> substrings;
	std::string substring = "";
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] != delimiter)
		{
			substring += str[i];
		}
		else
		{
			substrings.push_back(substring);
			while (str[i] == delimiter)
				i++;
			i--;
			substring = "";
		}
	}
	substrings.push_back(substring);
	return substrings;
}

void BitcoinExchange::read_input(std::string filepath)
{
	std::string	line;
	std::vector<std::string> date_value;
	std::ifstream file2(filepath);
	std::map<std::string, float>::iterator it;
	std::pair<std::string, float> p;

	if (!file2.is_open())
	{
		std::cerr << "error: can't open file." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::getline(file2, line);
	while(std::getline(file2, line))
	{
		date_value = this->split(line, '|');
		if (date_value[1].length() == 0 || date_value.size() < 2)
		{
			std::cout << "error: invalid input => " << date_value[0] << std::endl;
			continue;
		}
		it = this->_data.upper_bound(trim(date_value[0]));
		if (it != this->_data.end())
		{
			p = *(--it);
			try
			{
				if (std::stod(date_value[1]) > 1000)
					std::cout << "error: too large number." << std::endl;
				else if (std::stod(date_value[1]) < 0)
					std::cout << "error: positive number required." << std::endl;
				else
				{
					std::cout \
					<< date_value[0] << " => " << date_value[1] \
					<< " = " << std::stod(date_value[1]) * p.second \
					<< std::endl;
				}
			}
			catch (...)
			{
				std::cout << "error : input not number" << std::endl;
				continue;
			}
		}
	}
	file2.close();
}
