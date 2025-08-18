#include "PmergeMe.hpp"
#include <ctime>
#include <iostream>

int main(int argc, char** argv)
{
    clock_t totalStart = std::clock();  // START total timing

    PmergeMe sorter;
    if (sorter.processInput(argc, argv))
        return 1;

    std::vector<int> vec = sorter.getVector();
    std::list<int> lst = sorter.getList();

    clock_t sortVecStart = std::clock();
    sorter.performMergeSortVector(vec); // includes timing for sorting vector
    clock_t sortVecEnd = std::clock();

    clock_t sortListStart = std::clock();
    sorter.performMergeSortList(lst);   // includes timing for sorting list
    clock_t sortListEnd = std::clock();

    clock_t totalEnd = std::clock();    // END total timing

    // Total durations (input + sort) in microseconds
    double totalDuration = double(totalEnd - totalStart) * 1000000.0 / CLOCKS_PER_SEC;
    double totalVecDuration = double(sortVecEnd - totalStart) * 1000000.0 / CLOCKS_PER_SEC;
    double totalListDuration = double(totalEnd - sortVecEnd) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << "Total time for std::vector operations: " << totalVecDuration << " us" << std::endl;
    std::cout << "Total time for std::list operations: "   << totalListDuration << " us" << std::endl;

    return 0;
}
