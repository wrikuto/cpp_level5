#include <ctime>
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}


PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _lst(other._lst) {}


PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _lst = other._lst;
    }
    return (*this);
}


PmergeMe::~PmergeMe() {}


/**
 * ソートと時間計測を行う関数。
 *
 * 与えられた整数リストをベクトルとリストの2つの異なるデータ構造に対し、
 * ヤコブスタール数列を用いたマージ挿入ソートを実行し、ソートにかかった時間を計測。
 *
 * @param input ソート対象の整数リスト。
 * @return なし (結果は標準出力に表示される)
 */
void PmergeMe::sort_and_measure_time(const std::vector<int> &input)
{
    _vec = input;
    _lst.assign(input.begin(), input.end());

    std::cout << "Before: ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    double vec_time = measure_sort_time(_vec);
    double lst_time = measure_sort_time(_lst);

    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << " ";
    std::cout << std::endl;

    std::cout \
    << "Time to process a range of " \
    << _vec.size() << " elements with std::vector: " \
    << vec_time << " us" << std::endl;

    std::cout \
    << "Time to process a range of " \
    << _lst.size() << " elements with std::list: " \
    << lst_time << " us" << std::endl;
}


/**
 * ヤコブスタール数列を生成する関数
 *
 * @param n 生成する数列の長さ
 * @return 生成されたヤコブスタール数列
 */
std::vector<size_t> PmergeMe::generate_jacobsthal_sequence(size_t n)
{
    std::vector<size_t> sequence;
    if (n == 0) return sequence;

    sequence.push_back(0);
    if (n == 1) return sequence;

    sequence.push_back(1);
    size_t i = 2;

    while (sequence.size() < n)
    {
        sequence.push_back(sequence[i-1] + 2 * sequence[i-2]);
        i++;
    }

    return sequence;
}


/**
 * ヤコブスタール数列に基づく挿入順序を生成する関数
 *
 * @param n 要素数
 * @return 挿入順序を表す配列
 */
std::vector<size_t> PmergeMe::generate_insertion_order(size_t n)
{
    std::vector<size_t> insertion_order;
    if (n <= 1) return insertion_order;

    // ヤコブスタール数列を生成
    size_t jacobsthal_length = 0;
    size_t temp = n;
    while (temp > 0)
    {
        jacobsthal_length++;
        temp >>= 1;
    }

    std::vector<size_t> jacobsthal = generate_jacobsthal_sequence(jacobsthal_length);

    // 挿入順序を生成
    insertion_order.push_back(1); // 最初の要素は常に1

    for (size_t i = 1; i < jacobsthal.size(); i++)
    {
        size_t start = jacobsthal[i];
        size_t end = (i + 1 < jacobsthal.size()) ? jacobsthal[i + 1] : n;

        // 降順に追加
        for (size_t j = end; j > start; j--)
        {
            if (j <= n)
                insertion_order.push_back(j);
        }
    }

    return insertion_order;
}


/**
 * ヤコブスタール数列を使用したマージ挿入ソート（Ford-Johnsonソート）
 *
 * 手順:
 * 1. コンテナの要素をペアに分割し、それぞれのペアの最小値と最大値を決定。
 * 2. ペアの最大値のみを再帰的にソート。
 * 3. ヤコブスタール数列に基づく最適な順序でペアの最小値を挿入。
 * 4. 要素数が奇数の場合、最後の要素は別途処理。
 *
 * @tparam Container 汎用的なコンテナ型
 * @param container ソート対象のコンテナ
 * @return なし (結果はコンテナに反映される)
 */
template <typename Container>
void PmergeMe::ford_johnson_sort(Container &container)
{
    size_t n = container.size();

    if (n <= 1)
        return ;

    // ペアを作成する
    std::vector<std::pair<int, int> > pairs;
    typename Container::iterator it = container.begin();
    int stray = -1;
    bool has_stray = false;

    // 要素をペアに分ける
    while (it != container.end())
    {
        int first = *it++;
        if (it != container.end())
        {
            int second = *it++;
            if (first > second)
                pairs.push_back(std::make_pair(second, first));
            else
                pairs.push_back(std::make_pair(first, second));
        }
        else
        {
            stray = first;
            has_stray = true;
        }
    }

    // ペアがない場合は終了
    if (pairs.empty())
        return;

    // 各ペアの大きい要素をメインチェーンとして取得
    std::vector<int> main_chain;
    std::vector<int> pend;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        main_chain.push_back(pairs[i].second);
        pend.push_back(pairs[i].first);
    }

    // メインチェーンを再帰的にソート
    ford_johnson_sort(main_chain);

    // ソート済みの結果を格納するベクトル
    std::vector<int> result = main_chain;

    // 挿入順序を生成
    std::vector<size_t> insertion_order = generate_insertion_order(pend.size());

    // 挿入順序に従って要素を挿入
    for (size_t i = 0; i < insertion_order.size() && i < pend.size(); i++)
    {
        size_t idx = insertion_order[i] - 1; // 0-indexedに調整
        if (idx < pend.size())
        {
            typename std::vector<int>::iterator pos =
                std::lower_bound(result.begin(), result.end(), pend[idx]);
            result.insert(pos, pend[idx]);
        }
    }

    // 奇数個の場合、残りの要素を挿入
    if (has_stray)
    {
        typename std::vector<int>::iterator pos =
            std::lower_bound(result.begin(), result.end(), stray);
        result.insert(pos, stray);
    }

    // 結果をコンテナにコピー
    std::copy(result.begin(), result.end(), container.begin());
}

/**
 * @brief ソートにかかる時間を計測する関数。
 *
 * コンテナに対してマージ挿入ソートを実行し、ソート処理にかかった時間をマイクロ秒単位で計測。
 *
 * @tparam Container ソート対象となるコンテナ型
 * @param container ソート対象のコンテナ
 * @return double ソートにかかった時間（マイクロ秒）
 */
template <typename Container>
double PmergeMe::measure_sort_time(Container &container)
{
    std::clock_t start = std::clock();
    ford_johnson_sort(container);
    std::clock_t end = std::clock();

    double elapsed_time_ms = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    return (elapsed_time_ms);
}


template void PmergeMe::ford_johnson_sort<std::vector<int> >(std::vector<int> &);
template void PmergeMe::ford_johnson_sort<std::list<int> >(std::list<int> &);
