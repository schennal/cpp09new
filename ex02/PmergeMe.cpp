/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:15:24 by schennal          #+#    #+#             */
/*   Updated: 2024/08/20 16:15:25 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(PmergeMe const& copy) {
    (void)copy;
}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(PmergeMe const& copy) {
    (void)copy;
    return *this;
}

PmergeMe::PmergeMe(int* arr, int size) {
    if (size == 0) return;

    // Initialize the vector and list with the array
    for (int i = 0; i < size; i++) {
        _array.push_back(arr[i]);
        _list.push_back(arr[i]);
    }
}

void PmergeMe::sort(void) {
    if (_array.size() == 0 || _list.size() == 0)
        throw std::runtime_error("Error: Cannot sort empty containers");

    std::cout << "Before:  ";
    print(_array);

    clock_t start = clock();
    _sortArray();
    clock_t end = clock();

    std::cout << "After:   ";
    print(_array);

    double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000000;
    std::cout << "Time to process a range of " << _array.size()
              << " elements with std::vector : " << duration << " us" << std::endl;

    start = clock();
    _sortList();
    end = clock();

    duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000000;
    std::cout << "Time to process a range of " << _list.size()
              << " elements with std::list   : " << duration << " us" << std::endl;
}

void PmergeMe::_sortArray(void) {
    bool hasStray = _array.size() % 2 != 0;
    std::vector<int>::iterator end = hasStray ? _array.end() - 1 : _array.end();

    // Form pairs and bubble sort the pairs
    for (std::vector<int>::iterator itr = _array.begin(); itr != end; itr += 2) {
        if (*itr < *(itr + 1))
            std::swap(*itr, *(itr + 1));
        for (std::vector<int>::iterator next = itr; next != end; next += 2) {
            if (*itr > *next) {
                std::swap(*itr, *next);
                std::swap(*(itr + 1), *(next + 1));
            }
        }
    }

    std::vector<int> main, pend;
    for (std::vector<int>::iterator itr = _array.begin(); itr != end; itr += 2) {
        main.push_back(*itr);
        pend.push_back(*(itr + 1));
    }
    if (hasStray)
        pend.push_back(_array.back());

    _array.clear();

    for (std::vector<int>::const_iterator itr = pend.begin(); itr != pend.end(); itr++) {
        int index = _binarySearch(main, *itr);
        main.insert(main.begin() + index, *itr);
    }

    _array = main;
}

void PmergeMe::_sortList(void) {
    bool hasStray = _list.size() % 2 != 0;
    std::list<int>::iterator end = hasStray ? --_list.end() : _list.end();

    for (std::list<int>::iterator itr = _list.begin(); itr != end; std::advance(itr, 2)) {
        std::list<int>::iterator next = itr;
        next++;
        if (*itr < *next)
            std::swap(*itr, *next);
    }

    // Bubble sort the pairs
    for (std::list<int>::iterator itr = _list.begin(); itr != end; itr++) {
        for (std::list<int>::iterator next = itr; next != end; next++) {
            if (*itr > *next)
                std::swap(*itr, *next);
        }
    }

    std::list<int> main, pend;
    for (std::list<int>::iterator itr = _list.begin(); itr != end; itr++) {
        main.push_back(*itr);
        pend.push_back(*(++itr));
    }
    if (hasStray)
        pend.push_back(_list.back());

    _list.clear();

    for (std::list<int>::const_iterator itr = pend.begin(); itr != pend.end(); ++itr) {
        int index = _binarySearch(main, *itr);
        std::list<int>::iterator mainItr = main.begin();
        std::advance(mainItr, index);
        main.insert(mainItr, *itr);
    }

    _list = main;
}

template <typename Container>
void PmergeMe::print(Container& con) {
    for (typename Container::const_iterator itr = con.begin(); itr != con.end(); itr++)
        std::cout << *itr << " ";
    std::cout << std::endl;
}

template <typename Container>
int PmergeMe::_binarySearch(Container& con, int target) {
    int low = 0;
    int high = con.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        typename Container::iterator itr = con.begin();
        std::advance(itr, mid);
        if (*itr == target)
            return mid;
        else if (*itr < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}
