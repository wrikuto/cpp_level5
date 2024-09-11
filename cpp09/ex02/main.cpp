
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "error: invalid arg." << std::endl;
		return (1);
	}

	try
	{
		std::vector<int> input;

		for (int i = 1; i < argc; i++)
		{
			int num = std::stoi(argv[i]);
			if (num < 0)
				throw std::runtime_error("error: Negative numbers are not allowed");
			input.push_back(num);
		}

		PmergeMe sorter;
		sorter.sort_and_measure_time(input);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}
