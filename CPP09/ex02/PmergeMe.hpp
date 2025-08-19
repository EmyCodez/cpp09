#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <cstdlib> // For atoi

#define MAX_LIMIT 3000

class PmergeMe
{
private:
    std::vector<int> vecNumbers;
    std::list<int> lstNumbers;

    // Sorting helpers
    void fordJohnsonVector(std::vector<int>& data);
    void fordJohnsonList(std::list<int>& data);
    std::vector<int> generateJacobsthalSequence(int n);

public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    int processInput(int argc, char** argv);

    void performMergeSortVector(std::vector<int>& vec);
    void performMergeSortList(std::list<int>& lst);
    void sortVector(); 
    void sortList();   

    void printVector(const std::string& word);
    void printList();

    // Accessors 
    const std::vector<int>& getVector() const;
    const std::list<int>& getList() const;
};

#endif