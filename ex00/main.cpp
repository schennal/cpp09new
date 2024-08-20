/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:37:28 by schennal          #+#    #+#             */
/*   Updated: 2024/08/19 18:07:57 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }
    
    BitcoinExchange btc;
    if (!btc.loadData("data.csv")) {
        return 1;
    }
    
    btc.processInputFile(argv[1]);
    return 0;
}

// int main(int argc, char* argv[]) {
//     if (argc != 2) {
//         std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
//         return 1;
//     }

//     BitcoinExchange btc;

//     try {
//         // Load data from a fixed file
//         if (!btc.loadDataBase("data.csv")) {
//             std::cerr << "Failed to load data from 'data.csv'" << std::endl;
//             return 1;
//         }

//         // Process input from the command-line argument
//         btc.processInput(argv[1]);
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }
