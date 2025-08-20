#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    this->prices = other.prices;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    if (this != &other) {
        this->prices = other.prices;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        std::cerr << "Error: could not open data file.\n";
        std::exit(1);
    }

    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty() || line == "date,exchange_rate")
            continue;

        std::istringstream iss(line);
        std::string dateStr, rateStr;
        if (!std::getline(iss, dateStr, ',') ||
            !std::getline(iss, rateStr)) {
            std::cerr << "Error: bad data line: " << line << "\n";
            std::exit(1);
        }

        double rate = std::atof(rateStr.c_str());
        prices[dateStr] = rate;
    }
}

void BitcoinExchange::processInputFile(const std::string& filename) const {
    std::ifstream ifs(filename.c_str());
    if (!ifs.is_open()) {
        std::cerr << "Error: could not open input file.\n";
        std::exit(1);
    }

    std::string line;
    bool headerSeen = false;

    while (std::getline(ifs, line)) {
        if (line.empty())
            continue;

        if (line == "date | value") {
            if (headerSeen) {
                std::cerr << "Error: multiple headers detected.\n";
                continue;
            }
            headerSeen = true;
            continue;
        }

        std::size_t pipePos = line.find('|');
        if (pipePos == std::string::npos || line.find('|', pipePos + 1) != std::string::npos) {
            std::cerr << "Error: bad input => " << line << "\n";
            continue;
        }

        std::string datePart = line.substr(0, pipePos);
        std::string valuePartAndTrailing = line.substr(pipePos + 1);

        // Trim datePart
        datePart.erase(0, datePart.find_first_not_of(" \t"));
        datePart.erase(datePart.find_last_not_of(" \t") + 1);

        // Trim valuePart from left only
        std::string valuePart = valuePartAndTrailing;
        valuePart.erase(0, valuePart.find_first_not_of(" \t"));

        // Extract only the numeric part of the value
        std::istringstream valStream(valuePart);
        std::string numericPart;
        valStream >> numericPart;

        // Check for unexpected characters after numeric value
        std::string remainder;
        std::getline(valStream, remainder);

        bool badInput = false;
        for (std::size_t i = 0; i < remainder.length(); ++i) {
            if (remainder[i] != ' ' && remainder[i] != '\t') {
                std::cerr << "Error: bad input => " << line << "\n";
                badInput = true;
                break;
            }
        }
        if (badInput)
            continue;

        double value;
        if (!validateDate(datePart) || !validateValue(numericPart, value)) {
            std::cerr << "Error: bad input => " << line << "\n";
            continue;
        }

        std::map<std::string, double>::const_iterator it = prices.lower_bound(datePart);
        if (it == prices.end() || it->first != datePart) {
            if (it == prices.begin()) {
                std::cerr << "Error: no data available before " << datePart << "\n";
                continue;
            }
            --it;
        }

        printExchange(datePart, value, it->second);
    }
}

bool BitcoinExchange::validateDate(const std::string& date) const {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        std::cerr << "Error: bad input => " << date << "\n";
        return false;
    }

    int y = std::atoi(date.substr(0, 4).c_str());
    int m = std::atoi(date.substr(5, 2).c_str());
    int d = std::atoi(date.substr(8, 2).c_str());

    if (!isValidCalendarDate(y, m, d)) {
        std::cerr << "Error: bad input => " << date << "\n";
        return false;
    }
    return true;
}

bool BitcoinExchange::validateValue(const std::string& str, double& outValue) const {
    std::istringstream iss(str);
    if (!(iss >> outValue)) {
        std::cerr << "Error: bad input => " << str << "\n";
        return false;
    }
    if (outValue <= 0) {
        std::cerr << "Error: not a positive number.\n";
        return false;
    }
    if (outValue > 1000) {
        std::cerr << "Error: too large a number.\n";
        return false;
    }
    return true;
}

bool BitcoinExchange::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isValidCalendarDate(int y, int m, int d) {
    static const int mdays[] = { 31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31 };
    if (m < 1 || m > 12 || d < 1) return false;
    int maxd = mdays[m - 1];
    if (m == 2 && isLeapYear(y)) maxd = 29;
    return d <= maxd;
}

void BitcoinExchange::printExchange(const std::string& date, double value, double rate) const {
    double result = value * rate;
    std::cout << date << " => " << value << " = " << result << "\n";
}
