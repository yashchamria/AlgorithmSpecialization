/******************************************************************************************
********** Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming *************
******************************************************************************************/

/**************************** Weighted Independent Set **********************************/

#include <fstream>
#include <iostream>
#include <vector>

using Vertex = uint32_t;
using Weight = uint32_t;

std::vector<Vertex> GetIndependentSet(const std::vector<Vertex>& data)
{
	std::vector<Weight> memoizationSet(data.size() + 1);

	memoizationSet[0] = 0;
	memoizationSet[1] = data[0];

	for(int i = 2; i < memoizationSet.size(); ++i)
	{
		memoizationSet[i] = std::max(memoizationSet[i - 1], memoizationSet[i - 2] + data[i - 1]);
	}

	// Generating the independent set.
	std::vector<Vertex> independentSet;

	int i = memoizationSet.size() - 1;
	for(; i > 1; --i)
	{
		if(memoizationSet[i - 1] < memoizationSet[i - 2] + data[i - 1])
		{
			independentSet.push_back(i);
			--i;
		}
	}
	if (i == 1) { independentSet.push_back(i); }

	return independentSet;
}

int main()
{
	// Reading the input.
	std::cout << "Reading input...\r";
	std::ifstream inputFile{ "../IndependentSet/Data.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}
	
	Vertex vertexCount {0};
	inputFile >> vertexCount;
	
	std::vector<Weight> data(vertexCount);
	
	Vertex index {0};
	for (Weight weight; inputFile >> weight;)
	{
		data[index++] = weight;
	}
	inputFile.close();

	//const std::vector<Weight> smallData {6, 4, 3, 9, 10, 5, 2, 2};
	const auto independentSet = GetIndependentSet(data);

	std::cout << "Independent Set: " << "\n";

	for (int i = independentSet.size() - 1; i >= 0; --i)
	{
		std::cout << independentSet[i] << (i == 0 ? "." : ", ");
	}

	std::cin.get();
	return 0;
}