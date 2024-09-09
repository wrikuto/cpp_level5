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




// Ford-Johnsonアルゴリズムによるソート関数
template <typename Container>
void PmergeMe::ford_johnson_sort(Container &container)
{
    // コンテナの要素数を取得
    size_t n = container.size();
    if (n <= 1)
        return;

    // 2つのグループに分割してペアにする
    std::vector<std::pair<int, int> > pairs;
    typename Container::iterator it = container.begin(); // C++98準拠のためautoを使用しない
    while (it != container.end())
    {
        int first = *it;
        ++it;
        if (it != container.end())
        {
            int second = *it;
            pairs.push_back(std::make_pair(std::min(first, second), std::max(first, second)));
            ++it;
        }
        else
        {
            // 奇数の場合、最後の要素をそのまま格納
            pairs.push_back(std::make_pair(first, first));
        }
    }

    // 各ペアの最大値を抽出し、再帰的にソート
    std::vector<int> max_values;
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        max_values.push_back(pairs[i].second);
    }
    ford_johnson_sort(max_values); // 再帰的にソート

    // ソートされた最大値のリストにペアの最小値を挿入
    std::vector<int> sorted_sequence = max_values;
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        // 挿入位置を見つける
        typename std::vector<int>::iterator position = std::lower_bound(sorted_sequence.begin(), sorted_sequence.end(), pairs[i].first);

        // 挿入する値が最大値リストにない場合のみ挿入
        if (position == sorted_sequence.end() || *position != pairs[i].first)
        {
            sorted_sequence.insert(position, pairs[i].first);
        }
    }

    // ソート済みの結果をコンテナにコピー
    std::copy(sorted_sequence.begin(), sorted_sequence.end(), container.begin());
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
