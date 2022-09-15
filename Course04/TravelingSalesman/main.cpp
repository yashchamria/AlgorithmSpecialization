/******************************************************************************************
******** Shortest Paths Revisited, NP-Complete Problems and What To Do About Them *********
******************************************************************************************/

/****************************** Traveling Salesman Problem ***********************************/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

using Mask = int64_t;
using Location = uint32_t;
using Distance = double;
constexpr Distance Distance_Max = std::numeric_limits<Distance>::max();
using Position = std::pair<Distance, Distance>;

using Tour = std::vector<Location>;
using Graph = std::vector<Position>;
using AllPairPaths = std::vector<std::vector<Distance>>;
using MemoizationSet = std::vector<std::vector<Distance>>;

Distance GetOptimalTourDistance(const AllPairPaths& shortestPaths, MemoizationSet& memoizationSet, const Location start = 0, Mask visited = 1)
{
	if(visited == (1 << shortestPaths.size()) - 1) { return shortestPaths[start][0]; }

	if (memoizationSet[visited][start] < Distance_Max - 1.0) { return memoizationSet[visited][start]; }

	Distance minDistance = Distance_Max;

	for (Location i = 0; i < shortestPaths.size(); ++i)
	{
		if (!(visited & (1 << i)))
		{
			minDistance = std::min(minDistance, shortestPaths[start][i]
				+ GetOptimalTourDistance(shortestPaths, memoizationSet, i, visited | (1 << i)));
		}
	}

	return memoizationSet[visited][start] = minDistance;
}

Tour GetApproxOptimalTour(const AllPairPaths& shortestPaths)
{
	Tour tour;
	std::unordered_set<Location> visited;
	Location currentLocation = 0;

	while(visited.size() < shortestPaths.size())
	{
		visited.insert(currentLocation);
		tour.push_back(currentLocation);

		Location nextLocation {0};
		Distance minDistance {Distance_Max};

		for (Location i = 0; i < shortestPaths[currentLocation].size(); ++i)
		{
			if(!visited.contains(i) && shortestPaths[currentLocation][i] < minDistance)
			{
				nextLocation = i;
				minDistance = shortestPaths[currentLocation][i];
			}
		}

		currentLocation = nextLocation;
	}

	tour.push_back(0);
	return tour;
}

int main()
{
	// Dynamic programming approach -> exact algorithm feasible for small data set (20-25 nodes)
	#if 1
	{
		// Reading the input.
		std::cout << "Reading data...\r";
		std::ifstream inputFile{ "../TravelingSalesman/PositionData.txt", std::ios::in };
		if (!inputFile.is_open())
		{
			std::cout << "Failed to open the file!\n";
			return -1;
		}

		Location locationCount{ 0 };
		inputFile >> locationCount;

		Graph graph(locationCount);

		Location index{ 0 };
		for (Position position; inputFile >> position.first >> position.second;)
		{
			graph[index++] = position;
		}
		inputFile.close();

		std::cout << "Processing data...\r";
		MemoizationSet memoizationSet(1 << graph.size(), std::vector(graph.size(), Distance_Max));

		AllPairPaths shortestPaths(graph.size(), std::vector<Distance>(graph.size()));

		for (Location i = 0; i < graph.size(); ++i)
		{
			for (Location j = 0; j < graph.size(); ++j)
			{
				if (i == j) { continue; }

				shortestPaths[i][j] = std::sqrt(std::pow(graph[i].first - graph[j].first, 2)
					+ std::pow(graph[i].second - graph[j].second, 2));
			}
		}

		const auto minDistance = GetOptimalTourDistance(shortestPaths, memoizationSet);
		std::cout << "Minimum tour distance for a data set of size "<< graph.size() << " : " <<
			std::setprecision(std::numeric_limits<Distance>::digits10 + 1) << minDistance << "\n";
	}
	#endif

	// Greedy heuristic approach -> approximation algorithm.
	#if 1
	{
		// Reading the input.
		std::cout << "Reading data...\r";
		std::ifstream inputFile{ "../TravelingSalesman/PositionData_large.txt", std::ios::in };
		if (!inputFile.is_open())
		{
			std::cout << "Failed to open the file!\n";
			return -1;
		}

		Location locationCount {0};
		inputFile >> locationCount;

		Graph graph(locationCount);

		Location index {0};
		for (Position position; inputFile >> index >> position.first >> position.second;)
		{
			graph[index - 1] = position;
		}
		inputFile.close();

		std::cout << "Processing data...\r";

		AllPairPaths shortestPaths(graph.size(), std::vector<Distance>(graph.size()));

		for (Location i = 0; i < graph.size(); ++i)
		{
			for (Location j = 0; j < graph.size(); ++j)
			{
				if (i == j) { continue; }
				shortestPaths[i][j] = ((graph[i].first - graph[j].first) * (graph[i].first - graph[j].first))
					+ ((graph[i].second - graph[j].second) * (graph[i].second - graph[j].second));
			}
		}
		const auto tour = GetApproxOptimalTour(shortestPaths);

		Distance tourCost {0};

		for(Location i = 0; i < graph.size(); ++i)
		{
			tourCost += std::sqrt(shortestPaths[tour[i]][tour[i + 1]]);
		}
		std::cout << "Approx minimum tour distance for a data set of size " << graph.size() << " : " << std::setprecision(std::numeric_limits<Distance>::digits10 + 1) << tourCost << "\n";
	}
	#endif
	std::cin.get();
	return 0;
}