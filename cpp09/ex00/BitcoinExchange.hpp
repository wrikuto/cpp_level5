#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <string>
# include <vector>
# include <cctype>

class BitcoinExchange
{
	private:
		std::map <std::string, float>	_data;

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange& operator=(BitcoinExchange const &var);
		BitcoinExchange(BitcoinExchange const &var);

		void get_data(std::string date, float value);
		void read_input(std::string inputPath);
		std::map<std::string, float> get_data();
		std::vector<std::string> split(std::string str, char delimiter);
};

#endif
