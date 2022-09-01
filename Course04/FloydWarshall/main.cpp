/******************************************************************************************
******** Shortest Paths Revisited, NP-Complete Problems and What To Do About Them *********
******************************************************************************************/

/****************************** Floyd-Warshall Algorithm ***********************************/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using Vertex = uint32_t;
using Cost = int32_t;
using Edge = std::pair<std::pair<Vertex, Vertex>, Cost>;
using Graph = std::pair<Vertex, std::vector<Edge>>;
using CostNextVertexPair = std::pair<Cost, Vertex>;

std::vector<std::vector<CostNextVertexPair>> GetShortestPaths(const Graph& graph)
{
	// Initialize the memoization table.
	std::vector minCost(graph.first, std::vector(graph.first, CostNextVertexPair(INT32_MAX, 0)));
	for (Vertex i = 0; i < graph.first; ++i) { minCost[i][i] = {0, i + 1}; } // Sets self distance to zero.
	for (const auto& [edge, cost] : graph.second) // Sets the adjacent vertex distance and heads.
	{
		minCost[edge.first - 1][edge.second - 1] = {cost, edge.second};
	}

	// Fills the memoization table with shortest paths.
	for (Vertex i = 0; i < graph.first; ++i)
	{
		for (Vertex x = 0; x < graph.first; ++x)
		{
			for (Vertex y = 0; y < graph.first; ++y)
			{
				if(minCost[x][i].first != INT32_MAX && minCost[i][y].first != INT32_MAX)
				{
					const Cost newCost = minCost[x][i].first + minCost[i][y].first;
					if(minCost[x][y].first > newCost)
					{
						minCost[x][y] = { newCost, minCost[x][i].second};//i + 1};// minCost[i][y].second
					}
					//minCost[x][y].first = std::min(minCost[x][y].first, minCost[x][i].first + minCost[i][y].first);
				}
			}
		}
	}

	// Detects negative cycle by scanning diagonals for negative value.
	for (Vertex i = 0; i < graph.first; ++i) { if (minCost[i][i].first < 0) { return {}; } }

	return minCost;
}

int main()
{
	// Reading the input.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../FloydWarshall/g3.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}
	
	uint32_t VertexCount {0}, edgeCount {0};
	inputFile >> VertexCount >> edgeCount;
	
	Graph graph(VertexCount, (edgeCount));
	
	uint32_t index {0};
	for (Edge edge; inputFile >> edge.first.first >> edge.first.second >> edge.second;)
	{
		graph.second[index++] = edge;
	}
	inputFile.close();
	
	std::cout << "Processing data...\r";

	//constexpr uint32_t VertexCount {6};
	//const Graph graph(VertexCount, { {{1, 2}, 4}, {{2, 6}, -1}, {{2, 4}, 0}, {{3, 2}, 8}, {{4, 3}, 7}, {{4, 5}, -4}, {{5, 3}, -2}, {{6, 5}, 5} });
	const auto minCost = GetShortestPaths(graph);

	const auto generatePath = [&](const Vertex& start, const Vertex& end)
	{
		if (minCost[start - 1][end - 1].first == INT32_MAX) { return std::vector<Vertex>(); }

		std::vector path = {start};
		Vertex next {minCost[start - 1][end - 1].second};
		while(next != end)
		{
			path.push_back(next);
			next = minCost[next - 1][end - 1].second;
		}
		path.push_back(end);
		return path;
	};

	if(minCost.empty())
	{
		std::cout << "The input graph has negative cycle/s.";
	}
	else
	{
		std::cout << "Computed all pairs shortest path.\n";

		std::cout << "Select any vertices between 1 to " << VertexCount << " to get the path.\n";
		Vertex start {0}, end {0};
		std::cin >> start >> end;
		const auto path = generatePath(start, end);

		if(path.empty())
		{
			std::cout << "No Path is available from " << start << " to " << end << ".";
		}
		else
		{
			std::cout << "Shortest Path from " << start << " to " << end << " with a path cost of " << 
				(minCost[start - 1][end - 1].first == INT32_MAX ? "INF" : std::to_string(minCost[start - 1][end - 1].first)) << ":\n";

			for (const Vertex& vertex : path) { std::cout << vertex << (vertex == end ? "." : " -> "); }
		}
	}
	std::cin.get();
	return 0;
}