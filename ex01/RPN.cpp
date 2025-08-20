#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) {
	this->_stack = other._stack;
}

RPN &RPN::operator=(const RPN &other) {
	if (this != &other)
		this->_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

void RPN::parseAndCalculate(const std::string &expression) {
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token) {
		if (token.length() == 1 && std::string("+-*/").find(token[0]) != std::string::npos) {
			if (_stack.size() < 2)
				throw std::runtime_error("Error: insufficient operands.");

			int right = _stack.top(); _stack.pop();
			int left = _stack.top(); _stack.pop();
			int result = 0;

			switch (token[0]) {
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
					if (right == 0)
						throw std::runtime_error("Error: division by zero.");
					result = left / right;
					break;
				default:
					throw std::runtime_error("Error: invalid operator.");
			}
			_stack.push(result);
		}
		else {
			// Token should be a single digit number
			if (token.length() != 1 || token[0] < '0' || token[0] > '9')
				throw std::runtime_error("Error: invalid token '" + token + "'");
			_stack.push(std::atoi(token.c_str()));
		}
	}

	if (_stack.size() != 1)
		throw std::runtime_error("Error: invalid expression.");

	std::cout << _stack.top() << std::endl;
}
