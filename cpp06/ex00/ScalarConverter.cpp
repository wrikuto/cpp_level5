#include "ScalarConverter.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <limits>
ScalarConverter::ScalarConverter(void) 
{}

ScalarConverter::~ScalarConverter(void) 
{}

ScalarConverter::ScalarConverter(const ScalarConverter &) 
{}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) 
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
    if (str.length() > 1 && str[str.length() - 1] == 'f')
    {
        std::string temp = str.substr(0, str.length() - 1);
        std::istringstream iss(temp);
        float val;
        iss >> std::noskipws >> val;
        return (iss.eof() && !iss.fail());
    }
    return false;
}

static bool _isDouble(const std::string &str)
{
    std::istringstream iss(str);
    double val;

    iss >> std::noskipws >> val;
    return (iss.eof() && !iss.fail());
}

void ScalarConverter::convert(const std::string &literal) 
{
    if (literal == "nan" || literal == "nanf")
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
        return;
    }
    else if (literal == "+inf" || literal == "+inff")
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
        return;
    }
    else if (literal == "-inf" || literal == "-inff")
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
        return;
    }

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
            intValue = std::atoi(literal.c_str());
            charValue = static_cast<char>(intValue);
            floatValue = static_cast<float>(intValue);
            doubleValue = static_cast<double>(intValue);
        }
        else if (_isFloat(literal))
        {
            std::string temp = literal.substr(0, literal.length() - 1);
            floatValue = static_cast<float>(std::atof(temp.c_str()));
            intValue = static_cast<int>(floatValue);
            charValue = static_cast<char>(floatValue);
            doubleValue = static_cast<double>(floatValue);
        }
        else if (_isDouble(literal))
        {
            doubleValue = std::atof(literal.c_str());
            intValue = static_cast<int>(doubleValue);
            charValue = static_cast<char>(doubleValue);
            floatValue = static_cast<float>(doubleValue);
        }
        else
        {
            std::cout << "Conversion impossible" << std::endl;
            return;
        }
    }

    if (std::isprint(charValue))
        std::cout << "char: '" << charValue << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;

    std::cout << "int: " << intValue << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(1) << floatValue << "f" << std::endl;
    std::cout << "double: " << doubleValue << std::endl;

    return;
}