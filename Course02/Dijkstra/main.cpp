/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/******************** Dijkstra algorithm to find the shortest path ***********************/

#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using Vertex = uint32_t;
using Distance = uint32_t;
using AdjacentEdges = std::vector<std::pair<Vertex, Distance>>;
using Graph = std::vector<AdjacentEdges>;

constexpr auto MaxDistance = 1000000;

std::vector<Distance> GetShortestPath(const Graph& graph, const Vertex& startVertex)
{
	std::priority_queue<std::pair<Distance, Vertex>, std::vector<std::pair<Distance, Vertex>>, std::greater<>> openTiles;
	std::vector<Distance> minDistance(graph.size(), MaxDistance);

	openTiles.emplace(0, startVertex);
	minDistance[startVertex - 1] = 0;

	while(!openTiles.empty())
	{
		const Vertex visitingVertex = openTiles.top().second;
		openTiles.pop();

		for (const auto& adjacentVertex : graph[visitingVertex - 1])
		{
			const Distance distance = minDistance[visitingVertex - 1] + adjacentVertex.second;

			if (distance < minDistance[adjacentVertex.first - 1])
			{
				minDistance[adjacentVertex.first - 1] = distance;
				openTiles.emplace(distance, adjacentVertex.first);
			}
		}
	}

	return minDistance;
}

int main()
{
	// Reading the file.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../Dijkstra/GraphData.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

    Graph graph(200);

	for (std::string line; std::getline(inputFile, line); )
	{
		std::istringstream lineStream {line};
		Vertex head {0}, tail {0};
		Distance distance {MaxDistance};
		char comma = ',';
		lineStream >> tail;

		while(lineStream >> head >> comma >> distance)
		{
			graph[tail - 1].emplace_back(head, distance);
		}
	}
	inputFile.close();
	std::cout << "Processing data...\r";

	const auto& minDistance = GetShortestPath(graph, 1);

	std::cout << "Min Distance from:\n";

	for (int i = 0; i < minDistance.size(); ++i)
	{
		std::cout << "1 -> " << i + 1 << " = " << minDistance[i] << "\n";
	}

	std::cin.get();
    return 0;
}