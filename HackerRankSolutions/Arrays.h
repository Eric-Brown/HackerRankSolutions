#ifndef ARRAYS_H
#define ARRAYS_H

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <string>


class Arrays
{
private:
	const static std::string k_Chaotic_Queue_Msg;
	const static int k_Max_Bribes;
	std::vector<std::pair<int, size_t>> createValueIndexPairVector(std::vector<int> unsortedVector);
public:
	Arrays();
	~Arrays();
	std::vector<int> rotLeft(std::vector<int> toRotate, size_t numRotations);
	int minimumBribes(std::vector<int> queue);
	void minimumBribes(std::vector<int> queue, std::ostream_iterator<std::string> output);
	int minimumSwaps(std::vector<int> unsortedVector);
	long arrayManipulation(int n, std::vector<std::vector<int>> queries);
};

#endif // !ARRAYS_H



