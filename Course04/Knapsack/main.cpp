/******************************************************************************************
********** Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming *************
******************************************************************************************/

/******************************* 0/1 Knapsack problem ************************************/

#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <ranges>

using Value = uint32_t;
using Weight = uint32_t;
using Item = std::pair<Value, Weight>;
using Sack = std::vector<Item>;

Sack GetOptimalSack(const Sack& data, const Weight capacity, const float epsilon)
{
	// Drops the item values based on the epsilon.
	const Value averageValue = std::accumulate(data.cbegin(), data.cend(), 0,
		[](int sum, const auto& item) { return sum + std::get<0>(item); }) / data.size();

	Sack optimizedData = data;
	for (auto& value : optimizedData | std::views::keys)
	{
		value /= ((1.0f - epsilon) * averageValue);
	}

	// Dynamic algorithm to generate the memoization table on the optimized data.
	const Value maxValue = std::accumulate(optimizedData.cbegin(), optimizedData.cend(), 0,
		[](int sum, const auto& item) { return sum + std::get<0>(item); });

	std::vector memoizationSet(optimizedData.size() + 1, std::vector<Weight>(maxValue + 1, 999999999));
	memoizationSet[0][0] = 0;

	for (int i = 1; i < memoizationSet.size(); ++i)
	{
		const Value highestValue = std::accumulate(optimizedData.cbegin(), optimizedData.cbegin() + i, 0,
			[](int sum, const auto& item) { return sum + std::get<0>(item); });

		for (Value value = 0; value <= highestValue; ++value)
		{
			const auto& item = optimizedData[i - 1];

			if (item.first > value)
			{
				memoizationSet[i][value] = memoizationSet[i - 1][value];
			}
			else
			{
				memoizationSet[i][value] = std::min(memoizationSet[i - 1][value], memoizationSet[i - 1][value - item.first] + item.second);
			}
		}
	}

	// Finds the optimal value.
	Value optimalValue = maxValue;
	for (const auto& weight : memoizationSet[optimizedData.size()] | std::views::reverse)
	{
		if(weight <= capacity) { break; }
		--optimalValue;
	}

	// Backtracking to find the items in the optimal solution.
	Sack optimalSack;
	uint32_t item = optimizedData.size();
	Value value = optimalValue;

	while (item > 0 && value > 0)
	{
		if (memoizationSet[item][value] < memoizationSet[item - 1][value])
		{
			optimalSack.push_back(data[item - 1]);
			value -= optimizedData[item - 1].first;
		}
		--item;
	}

	return optimalSack;
}

int main()
{
	// Reading the input.
	std::cout << "Reading input...\r";
	std::ifstream inputFile{ "../Knapsack/Data_big.txt", std::ios::in };
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

	std::cout << "Processing data...\r";

	//constexpr Weight sackCapacity = 7;
	//const Sack data{ {2, 3}, {2, 1}, {4, 3}, {5, 4}, {3, 2} };

	const auto knapsack = GetOptimalSack(data, sackCapacity, 0.96f);

	//Actual optimal value: 4243395
	std::cout << "Approx optimal value: " <<
		std::accumulate(knapsack.cbegin(), knapsack.cend(), 0,
			[](int sum, const auto& item) { return sum + std::get<0>(item); }) << "\n";

	std::cin.get();
	return 0;
}