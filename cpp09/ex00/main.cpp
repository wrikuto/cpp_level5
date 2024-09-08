#include "BitcoinExchange.hpp"


int main(int argc , char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "can't open file" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	BitcoinExchange btc;

	btc.read_input(argv[1]);

	return (0);
}