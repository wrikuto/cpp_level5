#include "PmergeMe.hpp"
#include <cstdlib>
#include <climits>

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
            char *endptr;
            long num = std::strtol(argv[i], &endptr, 10);
            
            if (*endptr != '\0' || endptr == argv[i])
                throw std::runtime_error("error: Invalid number format");
                
            if (num < 0)
                throw std::runtime_error("error: Negative numbers are not allowed");
            
            if (num > INT_MAX)
                throw std::runtime_error("error: Number too large");
                
            input.push_back(static_cast<int>(num));
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