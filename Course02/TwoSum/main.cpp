/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/************************** Two Sum for range of targets *********************************/

#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main()
{
	// Reading the file.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../TwoSum/data.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	// Sum must be in the range of [-10000, 10000].
	constexpr std::pair<int64_t, int64_t> sumRange(-10000, 10000);

	std::unordered_map<int64_t, std::unordered_set<int64_t>> data;
	std::unordered_set<int64_t> targets;

	int64_t number {0};
	for (std::string line; std::getline(inputFile, line);)
	{
		std::istringstream lineStream {line};
		lineStream >> number;
		data[number/(sumRange.second - sumRange.first)].insert(number);
	}
	inputFile.close();

	for (const auto& val : data | std::views::values)
	{
		for (const auto& x : val)
		{
			const auto& yBucket = data.find((((sumRange.second + sumRange.first) / 2) - x) / (sumRange.second - sumRange.first));

			if (yBucket != data.end())
			{
				for (auto y : yBucket->second)
				{
					const int64_t result = x + y;

					if (-10000 <= result && result <= 10000)
					{
						targets.insert(result);
					}
				}
			}
		}
	}

	std::cout << "Number of distinct numbers: " << targets.size();
	std::cin.get();
    return 0;
}