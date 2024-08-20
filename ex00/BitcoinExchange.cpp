/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:00:40 by schennal          #+#    #+#             */
/*   Updated: 2024/08/20 17:04:09 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <sstream>
#include <iomanip>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : historicalData(other.historicalData) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        historicalData = other.historicalData;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::loadData(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        handleError("Error: could not open file.");
        return false;
    }
    
    std::string line;
    // Skip the header line
    std::getline(file, line);
    while (std::getline(file, line)) {
        parseLine(line);
    }
    
    return true;
}

void BitcoinExchange::processInputFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        handleError("Error: could not open file.");
        return;
    }
    
    std::string line;
    // Skip the header line
    std::getline(file, line);
    while (std::getline(file, line)) {
        parseInputLine(line);
    }
}

bool BitcoinExchange::isValidDateFormat(const std::string& date) {
    if (date.length() != 10) return false; // Expected length for YYYY-MM-DD

    for (size_t i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') return false; // Hyphens must be at positions 4 and 7
        } else {
            if (!isdigit(date[i])) return false; // All other characters must be digits
        }
    }
    return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (!isValidDateFormat(date)) {
        return false;
    }

    int year, month, day;
    char dash1, dash2;
    std::istringstream dateStream(date);
    dateStream >> year >> dash1 >> month >> dash2 >> day;

    if (dash1 != '-' || dash2 != '-' || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Check the number of days in the month
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool leapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if ((leapYear && day > 29) || (!leapYear && day > 28)) {
            return false;
        }
    }

    return true;
}

bool BitcoinExchange::isValidDateRange(const std::string& date) {
    const std::string lowerBound = "2009-01-02";
    const std::string upperBound = "2022-03-29";

    return (date >= lowerBound && date <= upperBound);
}

void BitcoinExchange::parseLine(const std::string& line) {
    std::istringstream stream(line.c_str());
    std::string date;
    std::string value;
    
    // Read date and value from the CSV line
    if (!std::getline(stream, date, ',') || !std::getline(stream, value)) {
        handleError("Error: bad input => " + line);
        return;
    }
    
    date = trim(date);
    value = trim(value);
    
    // Validate the date
    if (!isValidDate(date) || !isValidDateRange(date)) {
        handleError("Error: invalid date => " + date);
        return;
    }

    
    double rate;
    try {
        rate = std::stod(value.c_str());
    } catch (...) {
        handleError("Error: bad input => " + line);
        return;
    }
    
    if (rate < 0) {
        handleError("Error: not a positive number.");
        return;
    }
    
    historicalData[date] = rate;
}

void BitcoinExchange::parseInputLine(const std::string& line) {
    std::istringstream stream(line.c_str());
    std::string date;
    std::string value;
    
    // Read date and value from the input line
    if (!std::getline(stream, date, '|') || !std::getline(stream, value)) {
        handleError("Error: bad input => " + line);
        return;
    }
    
    date = trim(date);
    value = trim(value);

     // Validate the date
    if (!isValidDate(date) || !isValidDateRange(date)) {
        handleError("Error: invalid date => " + date);
        return;
    }
    
    double amount;
    try {
        amount = std::stod(value.c_str());
    } catch (...) {
        handleError("Error: bad input => " + line);
        return;
    }
    
    if (amount < 0) {
        handleError("Error: not a positive number.");
        return;
    }
    
    if (amount > 1000) {
        handleError("Error: too large a number.");
        return;
    }
    
    std::string closestDate = findClosestDate(date);
    if (closestDate.empty()) {
        handleError("Error: date not found in data.");
        return;
    }
    
    double rate = historicalData.at(closestDate);
    double result = amount * rate;
    
    std::cout << date << " => " << amount << " = " << std::fixed << std::setprecision(2) << result << std::endl;
}

std::string BitcoinExchange::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

std::string BitcoinExchange::findClosestDate(const std::string& date) {
    std::string closestDate;
    for (std::map<std::string, double>::const_iterator it = historicalData.begin(); it != historicalData.end(); ++it) {
        if (it->first <= date && (closestDate.empty() || it->first > closestDate)) {
            closestDate = it->first;
        }
    }
    return closestDate;
}

void BitcoinExchange::handleError(const std::string& message) {
    std::cerr << message << std::endl;
}

