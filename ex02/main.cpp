/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:27:32 by schennal          #+#    #+#             */
/*   Updated: 2024/08/20 16:16:48 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>
#include <vector>
#include <list>

bool isSorted(int* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1])
            return false;
    }
    return true;
}

int main(int argc, char **argv) 
{
    if (argc < 2) 
	{
        std::cout << "Usage: ./PmergeMe [num1] [num2] ... [numN]" << std::endl;
        return 1;
    }


	for (int i = 1; i < argc; i++)
	{
		for (int j = 0; argv[i][j]; j++)
		{
			if (!std::isdigit(argv[i][j]))
			{
				if (std::isalpha(argv[i][j]))
				{
					std::cout << "Error: non-numeric character" << std::endl;
					return (1);
				}
				else
				{
					std::cout << "Error: invalid character/number" << std::endl;
					return (1);
				}				
			}
		}
	}

    int size = argc - 1;
    int* array = new int[size];

    for (int i = 1; i < argc; i++) {
        double num = strtod(argv[i], NULL);
        if (num < std::numeric_limits<int>::min() || num > std::numeric_limits<int>::max()) {
            std::cout << "Error: Input is beyond integer range" << std::endl;
            delete[] array;
            return 1;
        }
        array[i - 1] = static_cast<int>(num);
    }

    if (isSorted(array, size)) {
        std::cout << "Error: Array is already sorted." << std::endl;
        delete[] array;
        return 1;
    }

    PmergeMe pmergeMe(array, size);

    // Perform sorting
    try {
        pmergeMe.sort();
    } catch (std::exception& error) {
        std::cout << error.what() << std::endl;
        delete[] array;
        return 1;
    }

    delete[] array;
    return 0;
}
