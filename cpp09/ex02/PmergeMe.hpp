
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
	// PmergeMe.hpp に追加するメソッド宣言
	std::vector<size_t> generate_jacobsthal_sequence(size_t n);
	std::vector<size_t> generate_insertion_order(size_t n);

};

#endif
