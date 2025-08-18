#include "PmergeMe.hpp"
#include <ctime>
#include <iostream>

int main(int argc, char** argv)
{
    clock_t totalStart = std::clock();  // START total timing

    PmergeMe sorter;
    if (sorter.processInput(argc, argv))
        return 1;

    std::vector<int>& vec = sorter.getVector();  // Fix: use reference
    std::list<int>& lst = sorter.getList();

    sorter.performMergeSortVector(vec); // sorting + timing inside
    clock_t sortVecEnd = std::clock();  // Marks end of vector sorting

    sorter.performMergeSortList(lst);   // sorting + timing inside
    clock_t totalEnd = std::clock();    // END of everything

    // Total durations (input + sort) in microseconds
    double totalVecDuration = double(sortVecEnd - totalStart) * 1000000.0 / CLOCKS_PER_SEC;
    double totalListDuration = double(totalEnd - sortVecEnd) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << "Total time for std::vector operations: " << totalVecDuration << " us" << std::endl;
    std::cout << "Total time for std::list operations: "   << totalListDuration << " us" << std::endl;

    return 0;
}

