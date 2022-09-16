/******************************************************************************************
******** Shortest Paths Revisited, NP-Complete Problems and What To Do About Them *********
******************************************************************************************/

/****************************** Max Cut problem ***********************************/

#include <iostream>
#include <unordered_set>
#include <vector>

using Vertex = uint32_t;
using AdjacentVertex = Vertex;
using Graph = std::vector<std::vector<AdjacentVertex>>;
using VertexSet = std::unordered_set<Vertex>;

std::pair<VertexSet, VertexSet> GetMaxCutSet(const Graph& graph)
{
	VertexSet setA(graph.size() - 1), setB {0};
	for (Vertex vertex = 1; vertex < graph.size(); ++vertex) { setA.insert(vertex); }

	const auto localSearch = [&](VertexSet& internalSet, VertexSet& externalSet)
	{
		for (const auto& vertex : internalSet)
		{
			uint32_t internalCuts {0}, externalCuts {0};

			for (const auto& adjacentVertex : graph[vertex])
			{
				externalSet.contains(adjacentVertex) ? ++externalCuts : ++internalCuts;
			}

			if (externalCuts < internalCuts)
			{
				externalSet.insert(vertex);
				internalSet.erase(vertex);
				return true;
			}
		}
		return false;
	};

	// If neither of the sets requires any local optimization, exit the program.
	while (localSearch(setA, setB) || localSearch(setB, setA));

	return {setA, setB};
}

int main()
{
	/*********************************************************
			0 --------- 5
			| \       / | \
			|   \   /   |   \
			|     4     |     6
			|   /   \   |   /
			| /       \ | /
			1 --------- 3
			  \       /  
			    \   /    
			      2      
	**********************************************************/
	// Optimal solution: Sets => {0, 2, 4, 6} & {1, 3, 5}, Max cut => 9

	const Graph graph
	{
		{1, 4, 5},       // <- 0
		{0, 2, 3, 4},    // <- 1
		{1, 3},          // <- 2
		{1, 2, 4, 5, 6}, // <- 3
		{0, 1, 3, 5},    // <- 4
		{0, 3, 4, 6},    // <- 5
		{3, 5}           // <- 6
	};

	/*********************************************************
			0 --------- 2 --------- 4
			  \       /   \       /  
			    \   /       \   /    
			      X           X      
			    /   \       /   \    
			  /       \   /       \  
			1 --------- 3 --------- 5
	**********************************************************/
	// Optimal solution: Sets => {2, 3} & {0, 1, 4, 5}, Max cut => 8

	//const Graph graph
	//{
	//	{2, 3},       // <- 0
	//	{2, 3},       // <- 1
	//	{0, 1, 4, 5}, // <- 2
	//	{0, 1, 4, 5}, // <- 3
	//	{2, 3},       // <- 4
	//	{2, 3},       // <- 5
	//};

	/*********************************************************
		0 --------- 2 --------- 4
		| \       / | \       / |
		|   \   /   |   \   /   |
		|     X     |     X     |
		|   /   \   |   /   \   |
		| /       \ | /       \ |
		1 --------- 3 --------- 5
	**********************************************************/
	// Optimal solution: Sets => {2, 3} & {0, 1, 4, 5}, Max cut => 8

	//const Graph graph
	//{
	//	{1, 2, 3},       // <- 0
	//	{0, 2, 3},       // <- 1
	//	{0, 1, 3, 4, 5}, // <- 2
	//	{0, 1, 2, 4, 5}, // <- 3
	//	{2, 3, 5},       // <- 4
	//	{2, 3, 4},       // <- 5
	//};

	const auto maxCutSet = GetMaxCutSet(graph);

	uint32_t maxCuts {0};
	for (const auto& vertex : maxCutSet.first)
	{
		for (const auto& adjacentVertex : graph[vertex])
		{
			if (maxCutSet.second.contains(adjacentVertex)) { ++maxCuts; }
		}
	}

	std::cout << "Approx maximum cuts: " << maxCuts << "\n";
	std::cin.get();
	return 0;
}