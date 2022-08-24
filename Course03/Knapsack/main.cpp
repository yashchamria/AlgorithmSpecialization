/******************************************************************************************
********** Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming *************
******************************************************************************************/

/******************************* 0/1 Knapsack problem ************************************/

#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using Value = uint32_t;
using Weight = uint32_t;
using Item = std::pair<Value, Weight>;
using Sack = std::vector<Item>;

Sack GetOptimalSack(const Sack& data, const uint32_t capacity)
{
	std::vector memoizationSet(data.size() + 1, std::vector<Weight>(capacity + 1)); // 2D array of item V Weight.

	for (int i = 1; i < memoizationSet.size(); ++i)
	{
		const auto& item = data[i - 1];

		for (int j = 1; j < memoizationSet[i].size(); ++j)
		{
			// if item weight is greater than the sack capacity then simply copy the previous values.
			if (item.second > j)
			{
				memoizationSet[i][j] = memoizationSet[i - 1][j];
			}
			else
			{
				memoizationSet[i][j] = std::max(memoizationSet[i - 1][j], memoizationSet[i - 1][j - item.second] + item.first);
			}
		}
	}

	// Backtracking to find the items in the optimal solution.
	Sack optimalSack;

	size_t i{ memoizationSet.size() - 1 }, j{ capacity };
	while (i > 0 && j > 0)
	{
		if (memoizationSet[i][j] > memoizationSet[i - 1][j])
		{
			optimalSack.push_back(data[i - 1]);
			j -= data[i - 1].second;
		}
		--i;
	}

	return optimalSack;
}

int main()
{
	// Reading the input.
	std::cout << "Reading input...\r";
	std::ifstream inputFile{ "../Knapsack/Data.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	uint32_t itemCount{ 0 }, sackCapacity{ 0 };
	inputFile >> sackCapacity >> itemCount;

	Sack data(itemCount);

	uint32_t index{ 0 };
	for (Item item; inputFile >> item.first >> item.second;)
	{
		data[index++] = item;
	}
	inputFile.close();

	//sackCapacity = 7;
	//const Sack smallData2{ {2, 3}, {2, 1}, {4, 3}, {5, 4}, {3, 2} };
	const auto knapsack = GetOptimalSack(data, sackCapacity);

	std::cout << "Maximum value: " <<
		std::accumulate(knapsack.cbegin(), knapsack.cend(), 0, [](int sum, const auto& item) { return sum + std::get<0>(item); });

	std::cin.get();
	return 0;
}