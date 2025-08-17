#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange {
public:
    BitcoinExchange();
    ~BitcoinExchange();

    // Load price database from CSV (data.csv)
    void loadDatabase(const std::string& filename);

    // Process input file and compute conversions
    void processInputFile(const std::string& filename) const;

private:
    std::map<std::string, double> prices;

    // Helpers to validate input fields
    bool validateDate(const std::string& date) const;
    bool validateValue(const std::string& str, double& outValue) const;

    // Check date with calendars and leap years
    static bool isLeapYear(int year);
    static bool isValidCalendarDate(int year, int month, int day);

    // Display result
    void printExchange(const std::string& date, double value, double rate) const;
};

#endif