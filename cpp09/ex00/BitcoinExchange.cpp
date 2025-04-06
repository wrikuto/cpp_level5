#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <sstream>

static std::string& trim(std::string& s)
{
    s.erase(0, s.find_first_not_of(" \t\n"));
    s.erase(s.find_last_not_of(" \t\n") + 1);
    return (s);
}

bool BitcoinExchange::isValidDateFormat(const std::string& date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i]))
            return false;
    }
    
    int year, month, day;
    std::stringstream ss(date);
    char delimiter;
    ss >> year >> delimiter >> month >> delimiter >> day;
    
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;
        
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    
    if (month == 2) {
        bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if ((isLeap && day > 29) || (!isLeap && day > 28))
            return false;
    }
    
    return true;
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
        std::cerr << "Error: could not open file." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::getline(file, line);
    while(std::getline(file, line))
    {
        point = line.find(',');
        if (point == std::string::npos)
        {
            std::cerr << "Error: invalid parameter" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        date = line.substr(0, point);
        try
        {
            value = std::atof(line.substr(point + 1).c_str());
        } 
        catch (...)
        {
            std::cerr << "Error: can't parse value" << std::endl;
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


void BitcoinExchange::split(std::string str, char delimiter, std::string& first, std::string& second)
{
    first = "";
    second = "";
    
    size_t i = 0;
    bool foundDelimiter = false;
    
    while (i < str.length())
    {
        if (str[i] == delimiter)
        {
            foundDelimiter = true;
            i++;
            while (i < str.length() && str[i] == delimiter)
                i++;
            break;
        }
        first += str[i];
        i++;
    }
    
    while (i < str.length())
    {
        second += str[i];
        i++;
    }
}

void BitcoinExchange::read_input(std::string filepath)
{
    std::string	line;
    std::string date_part, value_part;
    std::ifstream file2(filepath.c_str());
    std::map<std::string, float>::iterator it;
    std::pair<std::string, float> p;

    if (!file2.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::getline(file2, line);
    while(std::getline(file2, line))
    {
        this->split(line, '|', date_part, value_part);
        if (value_part.length() == 0)
        {
            std::string trimmed_date = date_part;
            trim(trimmed_date);
            std::cout << "Error: bad input => " << trimmed_date << std::endl;
            continue;
        }
        
        std::string trimmed_date = trim(date_part);
        
        if (!isValidDateFormat(trimmed_date))
        {
            std::cout << "Error: bad input => " << trimmed_date << std::endl;
            continue;
        }
        
        it = this->_data.upper_bound(trimmed_date);
        
        if (it == this->_data.begin())
        {
            std::cout << "Error: no date found before " << trimmed_date << std::endl;
            continue;
        }
        
        p = *(--it);
        try
        {
            float value = std::atof(trim(value_part).c_str());
            if (value > 1000)
                std::cout << "Error: too large a number." << std::endl;
            else if (value < 0)
                std::cout << "Error: not a positive number." << std::endl;
            else
            {
                std::cout 
                << trimmed_date << " => " << value
                << " = " << value * p.second
                << std::endl;
            }
        }
        catch (...)
        {
            std::cout << "Error: input not a number." << std::endl;
            continue;
        }
    }
    file2.close();
}