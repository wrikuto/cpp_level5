#include "converter.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

Converter::Converter(void) 
{}

Converter::~Converter(void) 
{}

Converter::Converter(const Converter &) 
{}

Converter &Converter::operator=(const Converter &) 
{
	return (*this);
}

static bool _isInteger(const std::string &str)
{
    std::istringstream iss(str);
    int val;

    iss >> std::noskipws >> val;
    return (iss.eof() && !iss.fail());
}

static bool _isFloat(const std::string &str)
{
    std::istringstream iss(str);
    float val;

    iss >> std::noskipws >> val;
    return (iss.eof() && !iss.fail());
}

static bool _isDouble(const std::string &str)
{
    std::istringstream iss(str);
    double val;

    iss >> std::noskipws >> val;
    return (iss.eof() && !iss.fail());
}

void Converter::convert(const std::string &literal) 
{
    char charValue;
    int intValue;
    float floatValue;
    double doubleValue;

    if (literal.length() == 1 && !std::isdigit(literal[0])) 
    {
        charValue = literal[0];
        intValue = static_cast<int>(charValue);
        floatValue = static_cast<float>(charValue);
        doubleValue = static_cast<double>(charValue);
    }
    else 
    {
        if (_isInteger(literal))
        {
            intValue = std::stoi(literal);
            charValue = static_cast<char>(intValue);
            floatValue = static_cast<float>(intValue);
            doubleValue = static_cast<double>(intValue);
        }
        else if (_isFloat(literal))
        {
            floatValue = std::stof(literal);
            intValue = static_cast<int>(floatValue);
            charValue = static_cast<char>(floatValue);
            doubleValue = static_cast<double>(floatValue);
        }
        else if (_isDouble(literal))
        {
            doubleValue = std::stod(literal);
            intValue = static_cast<int>(doubleValue);
            charValue = static_cast<char>(doubleValue);
            floatValue = static_cast<float>(doubleValue);
        }
        else
        {
            std::cout << "Conversion impossible" << std::endl;
            return ;
        }
    }

    if (std::isprint(charValue))
        std::cout << "char: '" << charValue << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;

    std::cout << "int: " << intValue << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(1) << floatValue << "f" << std::endl;
    std::cout << "double: " << doubleValue << std::endl;

    return ;
}