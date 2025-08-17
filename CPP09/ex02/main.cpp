#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	PmergeMe sorter;

	if (sorter.processInput(argc, argv))
		return 1;

	std::vector<int> vec = sorter.getVector();
	std::list<int> lst = sorter.getList();

	sorter.performMergeSortVector(vec);
	sorter.performMergeSortList(lst);

	return 0;
}
