#include "PmergeMe.hpp"

// コンストラクタ
PmergeMe::PmergeMe() {}

// コピーコンストラクタ
PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _lst(other._lst) {}

// 代入演算子
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _lst = other._lst;
    }
    return (*this);
}

// デストラクタ
PmergeMe::~PmergeMe() {}

// ソートと時間計測
void PmergeMe::sort_and_measure_time(const std::vector<int> &input)
{
    _vec = input;
    _lst.assign(input.begin(), input.end());

    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); ++i)
    {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;

    // std::vector に対する時間計測
    double vec_time = measure_sort_time(_vec);

    // std::list に対する時間計測
    double lst_time = measure_sort_time(_lst);

    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); ++i)
    {
        std::cout << _vec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector: " << vec_time << " us" << std::endl;
    std::cout << "Time to process a range of " << _lst.size() << " elements with std::list: " << lst_time << " us" << std::endl;
}

// Ford-Johnsonアルゴリズムによるソート
template <typename Container>
void PmergeMe::ford_johnson_sort(Container &container)
{
    if (container.size() <= 1)
        return;

    // ペアリングステップ: 要素をペアにしていく
    Container paired;
    typename Container::iterator it = container.begin();
    while (it != container.end())
    {
        typename Container::iterator next = it;
        ++next;
        if (next != container.end() && *it > *next)
            std::swap(*it, *next);  // 必要に応じて要素を交換

        paired.push_back(*it);  // ペアの中の小さい方を保存
        ++it;
        if (next != container.end()) ++it;
    }

    // 残った要素が奇数個の場合、最後の要素を直接追加
    if (container.size() % 2 != 0)
    {
        paired.push_back(container.back());
    }

    // 再帰的にFord-Johnsonソートを適用
    ford_johnson_sort(paired);

    // ペアの大きい方を挿入していく（挿入ソートに相当）
    typename Container::iterator insert_pos = paired.begin();
    for (typename Container::iterator i = insert_pos; i != container.end(); ++i)
    {
        if (std::find(paired.begin(), paired.end(), *i) == paired.end())  // ペアの大きい方かをチェック
        {
            typename Container::iterator pos = std::lower_bound(paired.begin(), insert_pos, *i);
            paired.insert(pos, *i);
        }
    }

    // 最終的な結果をコンテナに反映
    container = paired;
}

// Ford-Johnsonソートの時間計測
template <typename Container>
double PmergeMe::measure_sort_time(Container &container)
{
    std::clock_t start = std::clock();
    ford_johnson_sort(container);  // Ford-Johnsonソートを適用
    std::clock_t end = std::clock();
    return 1000000.0 * (end - start) / CLOCKS_PER_SEC;
}

// Explicit instantiation for the two types used
template void PmergeMe::ford_johnson_sort<std::vector<int> >(std::vector<int> &);
template void PmergeMe::ford_johnson_sort<std::list<int> >(std::list<int> &);
