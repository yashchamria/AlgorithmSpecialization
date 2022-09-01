/******************************************************************************************
******** Shortest Paths Revisited, NP-Complete Problems and What To Do About Them *********
******************************************************************************************/

/****************************** Johnson's Algorithm ***********************************/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using Vertex = uint32_t;
using Cost = int32_t;
using AdjacentEdge = std::pair<Vertex, Cost>;
using CostPreviousVertexPair = std::pair<Cost, Vertex>;
using Graph = std::vector<std::vector<AdjacentEdge>>;

std::vector<std::vector<CostPreviousVertexPair>> GetShortestPaths(Graph graph)
{
	// Runs BellmanFord algorithm to discover the vertex weights from a zero weight source vertex.
	std::vector vertexCost(graph.size(), 0);

	for (uint32_t i = 1; i < graph.size() + 1; ++i)
	{
		bool bRelaxed = false;

		for (Vertex tail = 1; tail <= graph.size(); ++tail)
		{
			for (const auto& [head, cost] : graph[tail - 1])
			{
				if (vertexCost[head - 1] > vertexCost[tail - 1] + cost)
				{
					bRelaxed = true;
					vertexCost[head - 1] = vertexCost[tail - 1] + cost;
				}
			} 
		}
		if (!bRelaxed) { break; }
		if (bRelaxed && i == graph.size()) { return {}; }
	}

	// Adjust edge weights.
	for (Vertex tail = 1; tail <= graph.size(); ++tail)
	{
		for (auto& [head, cost] : graph[tail - 1])
		{
			cost += vertexCost[tail - 1] - vertexCost[head - 1];
		}
	}

	// Runs Dijkstra's algorithm n times.
	std::vector allPairsPaths(graph.size(), std::vector(graph.size(), CostPreviousVertexPair(INT32_MAX, 0)));

	for (Vertex vertex = 1; vertex <= graph.size(); ++vertex)
	{
		std::priority_queue<CostPreviousVertexPair, std::vector<CostPreviousVertexPair>, std::greater<>> openTiles;
		std::vector minDistance(graph.size(), std::pair<Cost, Vertex>(INT32_MAX, 0));

		openTiles.emplace(0, vertex);
		minDistance[vertex - 1] = { 0, vertex };

		while (!openTiles.empty())
		{
			const Vertex visitingVertex = openTiles.top().second;
			openTiles.pop();

			for (const auto& adjacentVertex : graph[visitingVertex - 1])
			{
				const Cost cost = minDistance[visitingVertex - 1].first + adjacentVertex.second;

				if (cost < minDistance[adjacentVertex.first - 1].first)
				{
					minDistance[adjacentVertex.first - 1] = { cost, visitingVertex };
					openTiles.emplace(cost, adjacentVertex.first);
				}
			}
		}
		allPairsPaths[vertex - 1] = minDistance;
	}

	// Readjust the path edge weights.
	for (Vertex tail = 0; tail < graph.size(); ++tail)
	{
		for(Vertex head = 0; head < graph.size(); ++head)
		{
			if (allPairsPaths[tail][head].first != INT32_MAX)
			{
				allPairsPaths[tail][head].first += vertexCost[head] - vertexCost[tail];
			}
		}
	}
	return allPairsPaths;
}

int main()
{
	// Reading the input.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../Johnson/g3.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}
	
	uint32_t VertexCount {0}, edgeCount {0};
	inputFile >> VertexCount >> edgeCount;
	
	Graph graph(VertexCount);
	
	//uint32_t index {0};
	for (std::pair<std::pair<Vertex, Vertex>, Cost> edge; inputFile >> edge.first.first >> edge.first.second >> edge.second;)
	{
		graph[edge.first.first - 1].emplace_back(edge.first.second, edge.second);
	}
	inputFile.close();
	
	std::cout << "Processing data...\r";

	//Graph graph{{{2, 4}}, {{4, 0}, {6, -1}}, {{2, 8}}, {{3, 7}, {5, -4}}, {{3, -2}}, {{5, 5}}};
	const auto minCost = GetShortestPaths(graph);

	const auto generatePath = [&](const Vertex& start, const Vertex& end)
	{
		if (minCost[start - 1][end - 1].first == INT32_MAX) { return std::stack<Vertex>(); }
	
		std::stack<Vertex> path;
		path.push(end);
		Vertex previous {minCost[start - 1][end - 1].second};
		while (previous != start)
		{
			path.push(previous);
			previous = minCost[start - 1][previous - 1].second;
		}
		path.push(start);
		return path;
	};
	
	if (minCost.empty())
	{
		std::cout << "The input graph has negative cycle/s.";
	}
	else
	{
		std::cout << "Computed all pairs shortest path.\n";
	
		std::cout << "Select any vertices between 1 to " << graph.size() << " to get the path.\n";
		Vertex start{ 0 }, end{ 0 };
		std::cin >> start >> end;
		auto path = generatePath(start, end);
	
		if (path.empty())
		{
			std::cout << "No Path is available from " << start << " to " << end << ".";
		}
		else
		{
			std::cout << "Shortest Path from " << start << " to " << end << " with a path cost of " <<
				(minCost[start - 1][end - 1].first == INT32_MAX ? "INF" : std::to_string(minCost[start - 1][end - 1].first)) << ":\n";

			while(!path.empty())
			{
				const Vertex& vertex = path.top();
				path.pop();
				std::cout << vertex << (vertex == end ? "." : " -> ");
			}
		}
	}
	std::cin.get();
	return 0;
}