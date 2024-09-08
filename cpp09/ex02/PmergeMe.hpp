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

public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();
    
    // ソートと時間計測を行う関数
    void sort_and_measure_time(const std::vector<int> &input);

private:
    // Ford-Johnsonアルゴリズムによるソート関数
    template <typename Container>
    void ford_johnson_sort(Container &container);

    // 時間を計測するためのヘルパー関数
    template <typename Container>
    double measure_sort_time(Container &container);
};

#endif
