#include "stdafx.h"
#include "CppUnitTest.h"
#include "C:/Users/alexa/source/repos/HackerRankSolutions/HackerRankSolutions/Arrays.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ctime>
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HackerRankSolutionTests
{		
	TEST_CLASS(ArraysTests)
	{
	private:
		std::vector<int> createTestVector()
		{
			return std::vector<int>{1, 2, 3, 4, 5};
		}
		std::vector<int> createInvalidQueue()
		{
			return std::vector<int>{2, 5, 1, 3, 4 };
		}
		const std::string k_Chaotic_Msg{ "Too chaotic" };

	public:

		TEST_METHOD(ArraysCanLeftRotate)
		{
			Arrays toTest;
			std::vector<int> result = toTest.rotLeft(createTestVector(), 1);
			std::vector<int> expected{ 2,3,4,5,1 };
			Assert::IsTrue(expected == result);
		}
		TEST_METHOD(ArraysCanLeftRotateMultipleTimes)
		{
			Arrays toTest;
			std::vector<int> result = toTest.rotLeft(createTestVector(), 2);
			std::vector<int> expected{ 3,4,5,1,2 };
			Assert::IsTrue(expected == result);
		}
		TEST_METHOD(ArraysCanRotateItsSize)
		{
			Arrays toTest;
			std::vector<int> result = toTest.rotLeft(createTestVector(), 5);
			std::vector<int> expected{ 1,2,3,4,5 };
			Assert::IsTrue(expected == result);
		}

		TEST_METHOD(MiniumumBribeTrivialBribeCorrect)
		{
			Arrays toTest;
			std::vector<int> singleSwap = createTestVector();
			std::swap(singleSwap.at(0), singleSwap.at(1));
			Assert::IsTrue(toTest.minimumBribes(singleSwap) == 1);
		}

		TEST_METHOD(MinimumBribeBribelessQueueCorrect)
		{
			Arrays toTest;
			Assert::IsTrue(toTest.minimumBribes(createTestVector()) == 0);
		}

		TEST_METHOD(MinimumBribeMinimumBribesCorrect)
		{
			Arrays toTest;
			std::vector<int> bribe3Vec{ 2,1,5,3,4 };
			Assert::IsTrue(toTest.minimumBribes(bribe3Vec) == 3);
		}

		TEST_METHOD(MinimumBribesCalculatesProblematicMinimum)
		{
			//1 2 5 3 7 8 6 4
			//1 2 3 4 5 6 7 8
			//0 0 2 -1 2 2 -1 -4

			//foreach number, find first mismatch, calculate delta from original(?)

			//1 2 5 3 7 8 6 4
			//1 2 3 4 5 6 7 8
			//1 2 5 3 4 6 7 8 -- 2
				//5 moves up 2, other nodes are now -1 off before five and normal after 5
			//1 2 5 3 7 4 6 8 -- 2
				//7 moves up 2, 4 is -2 off, 6 is -1 off
			//1 2 5 3 7 8 4 6 -- 2
				//8 moves up 2, 4 is -3 off, 6 is -2 off
			//1 2 5 3 7 8 6 4 -- 1
				//6 moves up 1, 4 is -4 off
			Arrays toTest;
			std::vector<int> problemChild{ 1,2,5,3,7,8,6,4 };
			Assert::IsTrue(toTest.minimumBribes(problemChild) == 7);
		}


		TEST_METHOD(MinimumBribeReturnsNegativeWhenInvalidStateDetected)
		{
			Arrays toTest;
			std::vector<int> invalidQueue{ createInvalidQueue() };
			Assert::IsTrue(toTest.minimumBribes(invalidQueue) < 0);
		}

		TEST_METHOD(MinimumBribeReturnsNegativeForMoreComplicatedQueue)
		{
			Arrays toTest;
			std::vector<int> invalidLongQueue{ 2,5,1,3,4 };
			Assert::IsTrue(toTest.minimumBribes(invalidLongQueue) < 0);
		}

		TEST_METHOD(MinimumBribesOutputsToGivenIterator)
		{
			Arrays toTest;
			std::stringstream stream;
			std::vector<int> basicQueue = createTestVector();
			toTest.minimumBribes(basicQueue, stream);
			std::string result{};
			stream >> result;
			Assert::IsTrue(!result.empty());
		}


		TEST_METHOD(MinimumBribesOutputsChaoticMessageIfInvalid)
		{
			Arrays toTest;
			std::stringstream stream;
			std::vector<int> invalidQueue{ createInvalidQueue() };
			toTest.minimumBribes(invalidQueue, stream);
			std::string result{};
			std::getline(stream, result);
			Assert::IsTrue(!result.empty());
			Assert::AreEqual(k_Chaotic_Msg, result);
		}

	};
}