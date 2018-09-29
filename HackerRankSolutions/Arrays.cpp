#include "Arrays.h"

const std::string Arrays::k_Chaotic_Queue_Msg{ "Too chaotic" };
const int Arrays::k_Max_Bribes{ 2 };


std::vector<std::pair<int, size_t>> Arrays::createValueIndexPairVector(std::vector<int> unsortedVector)
{
	std::vector<std::pair<int, size_t>> valIndexVec{ unsortedVector.size() };
	auto iter = unsortedVector.begin();
	const auto start = unsortedVector.begin();
	auto generationLambda = [&iter, start]()
	{
		auto temp = iter;
		iter++;
		return std::pair<int, size_t>{(*temp), temp - start};
	};
	std::generate(valIndexVec.begin(), valIndexVec.end(), generationLambda);
	std::sort(valIndexVec.begin(), valIndexVec.end(), [](auto a, auto b)->bool { return a.first < b.first; });
	return valIndexVec;
}

Arrays::Arrays()
{
}



Arrays::~Arrays()
{
}

std::vector<int> Arrays::rotLeft(std::vector<int> toRotate, size_t numRotations)
{
	if (numRotations == 0) 
	{
		return toRotate;
	}
	std::vector<int> solution{};
	solution.reserve(toRotate.size());
	for (size_t i = 0; i < toRotate.size(); i++)
	{
		solution.push_back(toRotate.at((i + numRotations) % toRotate.size()));
	}
	return solution;
}


int Arrays::minimumBribes(std::vector<int> queue)
{
	if (queue.size() == 0 || std::is_sorted(queue.begin(), queue.end())) return 0;
	int totalBribes{};
	bool validState = true;
	for (int i = queue.size(); i > 0 && validState; --i)
	{
		std::vector<int> stack;
		while (queue.at(queue.size() - 1) != i)
		{
			stack.push_back(queue.back());
			queue.pop_back();
		}
		if (stack.size() > k_Max_Bribes)
		{
			validState = false;
			totalBribes = -1;
		}
		else
		{
			totalBribes += stack.size();
			queue.pop_back();
			std::copy(stack.rbegin(), stack.rend(), std::back_inserter(queue));
			stack.clear();
		}
	}
	return totalBribes;
}


//Rules:		a position can swap places with only the number directly in front of it
//				each element can bribe at most 2 times (2*size) == total
//Assumptions:	queue initially started as a set of natural numbers in increasing order i.e. 1,2,...,9,10
//Outputs:		prints to std::out result of minimum # of bribes
//				if the state is invalid (that is calculated bribes is greater than allowed) 'Too chaotic' is printed
void Arrays::minimumBribes(std::vector<int> queue, std::ostream_iterator<std::string> output)
{
	std::string resultMsg{};
	int result = minimumBribes(queue);
	if (result < 0)
	{
		resultMsg = k_Chaotic_Queue_Msg;
	}
	else
	{
		resultMsg = std::to_string(result);
	}
	*output = resultMsg;
}

int Arrays::minimumSwaps(std::vector<int> unsortedVector)
{
	std::vector<std::pair<int, size_t>> valueIndexVector{ createValueIndexPairVector(unsortedVector) };
	std::vector<bool> visited ( valueIndexVector.size(), false );
	int swaps{};
	for (size_t i = 0; i < valueIndexVector.size(); i++)
	{
		int cycleCount{};
		if (!visited.at(i))
		{
			visited.at(i) = true;
			size_t indexLink{ valueIndexVector.at(i).second };
			while (!visited.at(indexLink))
			{
				visited.at(indexLink) = true;
				++cycleCount;
				indexLink = valueIndexVector.at(indexLink).second;
			}
		}
		swaps += cycleCount;
	}
	return swaps;
}

//n : size of zero array
//queries : format of a b k
//		a : start index
//		b : end index
//		k : valToAdd
long Arrays::arrayManipulation(int n, std::vector<std::vector<int>> queries)
{
	//naive implementation --- sloooow
	std::vector<long> manipulatedVector(n);
	for (size_t i = 0; i < queries.size(); i++)
	{
		int index_a = queries[i][0] - 1;
		int index_b = queries[i][1];
		int valToAdd = queries[i][2];
		std::transform(manipulatedVector.begin() + index_a, manipulatedVector.begin() + index_b, manipulatedVector.begin() + index_a, [valToAdd](int a)-> int { return a + valToAdd; });
	}
	//what would be the god algorithm?
	for (size_t i = 0; i < n; i++)
	{
		//queries[i] = real total
	}
	//what about...
	for (size_t i = 0; i < queries.size(); i++)
	{
		//curr max = new max if any
		//actual 0 0 0 0 0
		// 1 2 200
		//heap (1,2,200)(3,5,0)
		//3 3 1000
		//heap (3,3,1000)(1,2,200)(4,5,0)
		//5 5 1000
		//heap (3,3,1000)(1,2,200)(5,5,1000)(4,4,0)
		//it's deteriorating into the original vector

	}
	return *std::max_element(manipulatedVector.begin(), manipulatedVector.end(), [](long a, long b)->bool {return a < b; });
}

