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
 * Ford-Johnsonソートを実行し、ソートにかかった時間を計測。
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
 * Ford-Johnsonアルゴリズムを使用してコンテナをソートする関数。
 *
 * 手順:
 * 1. コンテナの要素をペアに分割し、それぞれのペアの最小値と最大値を決定。
 * 2. ペアの最大値のみを再帰的にソート。
 * 3. ペアの最小値を、ソートされた最大値リストに挿入。
 * 4. 要素数が奇数の場合、最後の要素はダミーペアとして扱い、同じ値のペアを作成。
 * 5. 挿入時にダミー値を無視し、その他の値はすべて挿入。
 * 6. 最後にソートされた結果を元のコンテナにコピー。
 *
 * @tparam Container 汎用的なコンテナ型（例：std::vectorやstd::list）
 * @param container ソート対象のコンテナ
 * @return なし (結果はコンテナに反映される)
 */
template <typename Container>
void PmergeMe::ford_johnson_sort(Container &container)
{
	size_t n = container.size();

	if (n <= 1)
		return ;

	std::vector<std::pair<int, int> > pairs;
	typename Container::iterator it = container.begin();
	int dummy_value = -1;

	while (it != container.end())
	{
		int first = *it;
		++it;
		if (it != container.end())
		{
			int second = *it;
			pairs.push_back(
				std::make_pair(std::min(first, second), std::max(first, second))
				);
			++it;
		}
		else
		{
			pairs.push_back(std::make_pair(first, first));
			dummy_value = first;
		}
	}

	std::vector<int> max_values;
	for (size_t i = 0; i < pairs.size(); ++i)
		max_values.push_back(pairs[i].second);

	ford_johnson_sort(max_values);

	std::vector<int> sorted_sequence = max_values;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (pairs[i].first == dummy_value && pairs[i].second == dummy_value)
			continue; // ダミーを無視

		// 挿入位置を決定
		typename std::vector<int>::iterator position = \
			std::lower_bound(sorted_sequence.begin(), sorted_sequence.end(), pairs[i].first);

		sorted_sequence.insert(position, pairs[i].first);
	}

	std::copy(sorted_sequence.begin(), sorted_sequence.end(), container.begin());
}

/**
 * @brief ソートにかかる時間を計測する関数。
 * 
 * コンテナに対してFord-Johnsonソートを実行し、ソート処理にかかった時間をマイクロ秒単位で計測。
 * 
 * @tparam Container ソート対象となるコンテナ型（例：std::vectorやstd::list）。
 * @param container ソート対象のコンテナ。
 * @return double ソートにかかった時間（マイクロ秒）。
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
