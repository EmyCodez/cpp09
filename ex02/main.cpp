#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>
#include <sys/time.h>

double getElapsedTimeMicroseconds(const timeval& start, const timeval& end) {
    return static_cast<double>((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));
}

int main(int argc, char** argv)
{
    PmergeMe sorter;

    // ---------- Time input parsing ----------
    struct timeval inputStart, inputEnd;
    gettimeofday(&inputStart, NULL);
    if (sorter.processInput(argc, argv)) {
        return 1;
    }
    
    const std::vector<int>& vec = sorter.getVector();
    const std::list<int>& lst = sorter.getList();

    sorter.printVector("Before: ");
    gettimeofday(&inputEnd, NULL);

    double inputTime = getElapsedTimeMicroseconds(inputStart, inputEnd);

    // ---------- Time vector sort ----------
    struct timeval vecStart, vecEnd;
    gettimeofday(&vecStart, NULL);
    sorter.sortVector();
    gettimeofday(&vecEnd, NULL);

    double vecSortTime = getElapsedTimeMicroseconds(vecStart, vecEnd);
    double totalVecTime = inputTime + vecSortTime;

    // ---------- Time list sort ----------
    struct timeval listStart, listEnd;
    gettimeofday(&listStart, NULL);
    sorter.sortList();
    gettimeofday(&listEnd, NULL);

    double listSortTime = getElapsedTimeMicroseconds(listStart, listEnd);
    double totalListTime = inputTime + listSortTime;

    // ---------- Output timings ----------
    sorter.printVector("After: ");
    std::cout << "Time to process a range of " << vec.size()
          << " elements with std::vector : "
          << std::fixed << std::setprecision(4) << totalVecTime << " us" << std::endl;

    std::cout << "Time to process a range of " << lst.size()
              << " elements with std::list   : " 
              << std::fixed << std::setprecision(4) << totalListTime << " us" << std::endl;

    return 0;
}
