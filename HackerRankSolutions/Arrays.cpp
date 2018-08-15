#include "Arrays.h"

const std::string Arrays::k_Chaotic_Queue_Msg{ "Too chaotic" };
const int Arrays::k_Max_Bribes{ 2 };


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

