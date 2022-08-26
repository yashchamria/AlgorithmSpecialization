/******************************************************************************************
******** Shortest Paths Revisited, NP-Complete Problems and What To Do About Them *********
******************************************************************************************/

/****************************** Bellman–Ford Algorithm ***********************************/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using Vertex = uint32_t;
using Cost = int32_t;
using Edge = std::pair<std::pair<Vertex, Vertex>, Cost>;
using Graph = std::pair<Vertex, std::vector<Edge>>;

std::vector<std::pair<Cost, Vertex>> GetShortestPaths(const Graph& graph, const Vertex& source)
{
	std::vector<std::pair<Cost, Vertex>> minPath(graph.first, {INT32_MAX / 2, source}); // minCost and predecessor pair.

	minPath[source - 1] = {0, source};

	for (uint32_t i = 0; i < graph.first + 1; ++i)
	{
		bool bRelaxed = false;
		for(const auto& [edge, cost] : graph.second)
		{
			if(minPath[edge.second - 1].first > minPath[edge.first - 1].first + cost)
			{
				bRelaxed = true;
				minPath[edge.second - 1] = {minPath[edge.first - 1].first + cost, edge.first};
			}
		}

		if (!bRelaxed) { break; }
		if (bRelaxed && i == graph.first) { return {}; }
	}

	return minPath;
}

int main()
{
	// Reading the input.
	std::cout << "Reading input...\r";
	std::ifstream inputFile{ "../BellmanFord/g3.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	uint32_t VertexCount {0}, edgeCount{ 0 };
	inputFile >> VertexCount >> edgeCount;

	Graph graph(VertexCount, (edgeCount));

	uint32_t index {0};
	for (Edge edge; inputFile >> edge.first.first >> edge.first.second >> edge.second;)
	{
		graph.second[index++] = edge;
	}
	inputFile.close();

	constexpr Vertex source = 1;
	const auto minCost = GetShortestPaths(graph, source);

	if(minCost.empty())
	{
		std::cout << "The input graph has negative cycle/s.";
	}
	else
	{
		std::cout << "Predecessor and min distance:\n";

		for (int i = 0; i < minCost.size(); ++i)
		{
			std::cout << source << " -> .. " << std::setfill('0') << std::setw(3) << minCost[i].second
				<< " -> " << std::setfill('0') << std::setw(3) << i + 1 <<
				" = " << minCost[i].first << "\n";
		}
	}
	std::cin.get();
	return 0;
}