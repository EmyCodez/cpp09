#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

class RPN {
private:
	std::stack<int> _stack;

public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	void parseAndCalculate(const std::string &expression);
};

#endif
