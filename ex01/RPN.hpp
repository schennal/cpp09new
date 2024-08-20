/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schennal <schennal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:11:38 by schennal          #+#    #+#             */
/*   Updated: 2024/08/20 08:11:51 by schennal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <fstream>
#include <stdexcept> 
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

class RPN {
public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    void process(const std::string& expression);

private:
    std::stack<int> operands;
    void performOperation(char op, bool &errorOccurred);
    void handleError(const std::string& message);
};

#endif
