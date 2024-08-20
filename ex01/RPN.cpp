/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:35:35 by schennal          #+#    #+#             */
/*   Updated: 2024/08/17 13:35:49 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <cstdlib>  // for std::atoi
#include <iostream>

// Default Constructor
RPN::RPN() {}

// Copy Constructor
RPN::RPN(const RPN& other) : operands(other.operands) {}

// Assignment Operator
RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        operands = other.operands;
    }
    return *this;
}

// Destructor
RPN::~RPN() {}

void RPN::process(const std::string& expression) {
    std::istringstream stream(expression);
    std::string token;

    bool errorOccurred = false;
    while (stream >> token) {
        if (std::isdigit(token[0])) {
            operands.push(std::atoi(token.c_str()));
        } else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            if (operands.size() < 2) {
                handleError("Error: insufficient operands");
                errorOccurred = true;
                break;
            }
            performOperation(token[0], errorOccurred);
            if (errorOccurred) break; // Exit if an error occurred during operation
        } else {
            handleError("Error: invalid token");
            errorOccurred = true;
            break;
        }
    }

    if (!errorOccurred && operands.size() != 1) {
        handleError("Error: invalid expression");
    } else if (!errorOccurred && !operands.empty()) {
        std::cout << operands.top() << std::endl;
    }
}

void RPN::performOperation(char op, bool &errorOccurred) {
    int right = operands.top();
    operands.pop();
    int left = operands.top();
    operands.pop();
    int result;

    switch (op) {
        case '+':
            result = left + right;
            break;
        case '-':
            result = left - right;
            break;
        case '*':
            result = left * right;
            break;
        case '/':
            if (right == 0) {
                handleError("Error: division by zero");
                errorOccurred = true;
                return;
            }
            result = left / right;
            break;
        default:
            handleError("Error: unknown operator");
            errorOccurred = true;
            return;
    }

    operands.push(result);
}

void RPN::handleError(const std::string& message) {
    std::cerr << message << std::endl;
}
