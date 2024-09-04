#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <string>

class Converter
{
public:
	Converter();
	~Converter();
	Converter(const Converter &);
	Converter &operator=(const Converter &);

	static void convert(const std::string &literal);
};

#endif
