#include "stdafx.h"
#include "CppUnitTest.h"
#include "C:/Users/alexa/source/repos/HackerRankSolutions/HackerRankSolutions/Arrays.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <ctime>
#include <fstream>
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
		const size_t k_Nums_Per_Query_Line{ 3 };
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

		TEST_METHOD(MinimumBribeReturnsNegativeForMoreComplicatedQueue)
		{
			Arrays toTest;
			std::vector<int> invalidLongQueue{ 2,5,1,3,4 };
			Assert::IsTrue(toTest.minimumBribes(invalidLongQueue) < 0);
		}

		TEST_METHOD(MinimumSwapsIsCorrect)
		{
			Arrays toTest;
			std::vector<std::pair<std::vector<int>, int>> problemSolutionPairVector{
				{{7,1,3,2,4,5,6} , 5},
				{{4,3,1,2} , 3},
				{{2,3,4,1,5} , 3},
				{{1,3,5,2,4,6,8} , 3}
			};
			for each (std::pair<std::vector<int>,int> probSolPair in problemSolutionPairVector)
			{
				Assert::IsTrue(toTest.minimumSwaps(probSolPair.first) == probSolPair.second);
			}
		}

		TEST_METHOD(MinimumSwapsHandlesZeroSwapSolutions)
		{
			Arrays toTest;
			std::vector<int> easyZero{ 1,2,3,4,5 };
			std::vector<int> harderishZero{ 90,1000,10000 };
			Assert::IsTrue(toTest.minimumSwaps(easyZero) == 0);
			Assert::IsTrue(toTest.minimumSwaps(harderishZero) == 0);
		}

		TEST_METHOD(ArrayManipulationIsCorrect)
		{
			Arrays toTest;
			std::vector< std::pair< std::pair< size_t , std::vector< std::vector< int > > > , long> > argumentSolutionVector
			{
				{ {10, { {1,5,3}, {4,8,7}, {6,9,1} } }, 10},
				{ {5, { {1,2,100}, {2,5,100}, {3,4,100} } }, 200}
			};
			for each (auto actualExpectedPair in argumentSolutionVector)
			{
				Assert::IsTrue(toTest.arrayManipulation(actualExpectedPair.first.first, actualExpectedPair.first.second) == actualExpectedPair.second);
			}
		}

		TEST_METHOD(ArrayManipulationCanHandleLongQueries)
		{
			Arrays toTest;

			//TODO: Do a relative path and not absolute
			std::ifstream longQueryFile("c:\\Users\\alexa\\source\\repos\\HackerRankSolutions\\HackerRankSolutionTests\\LongTest.txt");
			std::istream_iterator<int> queryFileIter{ longQueryFile };
			int zeroVecSize = (*queryFileIter++);
			std::vector<std::vector<int>> queries((*queryFileIter++));
			std::generate(queries.begin(), queries.end(), 
				[&queryFileIter]()->std::vector<int>
			{
				std::vector<int> queryLine(3);
				std::generate(queryLine.begin(), queryLine.end(), [&queryFileIter]()->int
				{
					return (*queryFileIter++);
				});
				return queryLine;
			});
			Assert::IsTrue(toTest.arrayManipulation(zeroVecSize, queries) == 2510535321);
		}

	};
}