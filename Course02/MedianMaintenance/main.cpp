/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/*************************** Median maintenance using heaps ******************************/

#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>

using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<>>;
using MaxHeap = std::priority_queue<int>;

int main()
{
	// Reading the file.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../MedianMaintenance/UnsortedArray.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	MaxHeap bottom;
	MinHeap top;
	std::vector<int> medians;

	for (std::string line; std::getline(inputFile, line);)
	{
		std::istringstream lineStream {line};
		int number {0};
		lineStream >> number;

		// Inserting the elements.
		if (bottom.empty() || number < bottom.top())
		{
			bottom.push(number);
		}
		else
		{
			top.push(number);
		}

		// Balancing the heap size.
		// In case of odd entries bottom heap will always hold the extra element and algorithm assumes the median to be ((n + 1) / 2).
		if (top.size() > bottom.size())
		{
			bottom.push(top.top());
			top.pop();
		}
		else if(top.size() + 1 < bottom.size())
		{
			top.push(bottom.top());
			bottom.pop();
		}

		medians.push_back(bottom.top());
	}
	inputFile.close();

	std::cout << "Sum of medians -> " << std::accumulate(medians.cbegin(), medians.cend(), 0);

	std::cin.get();
    return 0;
}