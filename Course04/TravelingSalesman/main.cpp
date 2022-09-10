/******************************************************************************************
******** Shortest Paths Revisited, NP-Complete Problems and What To Do About Them *********
******************************************************************************************/

/****************************** Traveling Salesman Problem ***********************************/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using Mask = int64_t;
using Location = uint32_t;
using Distance = float;
constexpr Distance Distance_Max = std::numeric_limits<Distance>::max();
using Position = std::pair<Distance, Distance>;

using Tour = std::vector<Location>;
using Graph = std::vector<Position>;
using AllPairPaths = std::vector<std::vector<Distance>>;
using MemoizationSet = std::vector<std::vector<Distance>>;

AllPairPaths GetAllPairShortestPaths(const Graph& graph)
{
	AllPairPaths shortestPaths(graph.size(), std::vector<Distance>(graph.size()));

	for (Location i = 0; i < graph.size(); ++i)
	{
		for (Location j = 0; j < graph.size(); ++j)
		{
			if (i == j) { continue; }

			shortestPaths[i][j] = std::sqrtf(std::powf(graph[i].first - graph[j].first, 2)
				+ std::powf(graph[i].second - graph[j].second, 2));
		}
	}
	return shortestPaths;
}

Distance GetOptimalTour(const AllPairPaths& shortestPaths, MemoizationSet& memoizationSet, const Location start = 0, Mask visited = 1)
{
	if(visited == (1 << shortestPaths.size()) - 1) { return shortestPaths[start][0]; }

	if (memoizationSet[visited][start] < Distance_Max - 1.0f) { return memoizationSet[visited][start]; }

	Distance minDistance = Distance_Max;

	for (Location i = 0; i < shortestPaths.size(); ++i)
	{
		if (!(visited & (1 << i)))
		{
			minDistance = std::min(minDistance, shortestPaths[start][i]
				+ GetOptimalTour(shortestPaths, memoizationSet, i, visited | (1 << i)));
		}
	}

	return memoizationSet[visited][start] = minDistance;
}


int main()
{
	// Reading the input.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../TravelingSalesman/PositionData.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}
	
	Location locationCount {0};
	inputFile >> locationCount;
	
	Graph graph(locationCount);
	
	Location index {0};
	for (Position position; inputFile >> position.first >> position.second;)
	{
		graph[index++] = position;
	}
	inputFile.close();

	std::cout << "Processing data...\r";
	MemoizationSet memoizationSet(1 << graph.size(), std::vector(graph.size(), Distance_Max));
	const auto tour = GetOptimalTour(GetAllPairShortestPaths(graph), memoizationSet);
	std::cout << "Minimum tour distance: " << tour << "\n";

	std::cin.get();
	return 0;
}