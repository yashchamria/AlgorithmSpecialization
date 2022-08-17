/******************************************************************************************
********** Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming *************
******************************************************************************************/

/***************** Prim's algorithm to find the minimum spanning tree ********************/

#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <ranges>
#include <vector>

using Vertex = uint32_t;
using Cost = int32_t;
using AdjacentVertex = std::pair<Vertex, Cost>;
using Graph = std::vector<std::vector<AdjacentVertex>>;
using SpanningTree = std::vector<AdjacentVertex>;

SpanningTree GetMinimumSpanningTree(const Graph& graph)
{
	std::priority_queue<std::pair<Cost, Vertex>, std::vector<std::pair<Cost, Vertex>>, std::greater<>> openVertices;
	std::vector visited(graph.size(), false);
	SpanningTree mst(graph.size(), {0, INT32_MAX});

	openVertices.emplace(0, 0);
	mst[0] = {0, 0};

	while(!openVertices.empty())
	{
		const Vertex visitingVertex = openVertices.top().second;
		openVertices.pop();

		if(visited[visitingVertex]) { continue; }

		visited[visitingVertex] = true;

		for (const auto& adjacentVertex : graph[visitingVertex])
		{
			if (!visited[adjacentVertex.first] && adjacentVertex.second < mst[adjacentVertex.first].second)
			{
				openVertices.emplace(adjacentVertex.second, adjacentVertex.first);
				mst[adjacentVertex.first] = { visitingVertex, adjacentVertex.second };
			}
		}
	}
	return mst;
}

int main()
{
	// Reading the file.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../PrimMST/GraphData.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	uint32_t vertexCount {0}, edgeCount{0};
	inputFile >> vertexCount >> edgeCount;
	Graph graph(vertexCount);

	Cost cost {0};
	for (Vertex head {0}, tail {0}; inputFile >> tail >> head >> cost;)
	{
		graph[tail - 1].emplace_back(head - 1, cost);
		graph[head - 1].emplace_back(tail - 1, cost);
	}
	inputFile.close();

	const auto& mst = GetMinimumSpanningTree(graph);

	std::cout << "Minimum spanning tree cost: " <<
		std::accumulate(mst.cbegin(), mst.cend(), 0, [](int sum, const auto& vertex) { return sum + vertex.second; });

	std::cin.get();
    return 0;
}