#include <iostream>
#include "iter.hpp"


int main()
{
	int int_array[] = {1, 2, 3, 4, 5};
	std::string str_array[] = {"hello", "world", "!"};

	std::cout << "output int_array:" << std::endl;
	iter(int_array, 5, printElement);

	std::cout << "output str_array:" << std::endl;
	iter(str_array, 3, printElement);

	return (0);
}
