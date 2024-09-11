
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <stdexcept>

class PmergeMe
{
private:
	std::vector<int> _vec;
	std::list<int> _lst;

	template <typename Container>
	void ford_johnson_sort(Container &container);
	template <typename Container>
	double measure_sort_time(Container &container);

public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();

	void sort_and_measure_time(const std::vector<int> &input);


};

#endif
