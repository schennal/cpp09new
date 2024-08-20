/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:37:34 by schennal          #+#    #+#             */
/*   Updated: 2024/08/20 08:09:52 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP



#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept> 
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>  // For std::setprecision
#include <limits>   // For std::numeric_limits

#define DEFAULT   "\033[0m"
#define YELLOW    "\e[0;33m"
#define GREEN     "\033[1;32m"
#define CYAN      "\033[0;36m"
#define RED       "\e[0;31m"

class BitcoinExchange {
public:
    BitcoinExchange();

    BitcoinExchange(const BitcoinExchange& other);

    BitcoinExchange& operator=(const BitcoinExchange& other);

    ~BitcoinExchange();
    
    bool loadData(const std::string& filename);
    void processInputFile(const std::string& filename);
    
private:
    std::map<std::string, double> historicalData;

    void parseLine(const std::string& line);
    void parseInputLine(const std::string& line);
    void handleError(const std::string& message);
    std::string trim(const std::string& str);
    std::string findClosestDate(const std::string& date);
    
    // Method declarations for date validation
    bool isValidDateFormat(const std::string& date);
    bool isValidDate(const std::string& date);
    bool isValidDateRange(const std::string& date);
};

#endif

