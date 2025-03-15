#include "easyfind.hpp"
#include <vector>
#include <list>

int main()
{
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);

	try
	{
		std::vector<int>::iterator it = easyfind(vec, 20);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Value not found" << std::endl;
	}

	try
	{
		std::vector<int>::iterator it = easyfind(vec, 50);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Value not found" << std::endl;
	}

	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);
	
	try {
		std::list<int>::iterator it = easyfind(lst, 20);
		std::cout << "Found in list: " << *it << std::endl;
	} catch (const std::exception& e) {
		std::cout << "not found in list"<< std::endl;
	}

	return (0);
}
