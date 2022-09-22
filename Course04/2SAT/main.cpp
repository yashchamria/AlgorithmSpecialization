/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/***************************** Satisfiability(2-SAT) problem *****************************/

#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using Vertex = int;
using Index = int;
using Graph = std::vector<std::vector<Vertex>>;

static Index ToIndex(const Vertex vertex, const uint32_t variables) { return vertex > 0 ? vertex - 1 : variables - vertex - 1; }
static Vertex ToVertex(const int index, const uint32_t variables) { return index < variables ? index + 1 : variables - index - 1; }


bool IsSatisfiable(const Graph graph)
{
	std::vector visitedVertices(graph.size(), false);
	std::stack<Vertex> openTiles;

	const auto dfs = [&](const auto& dfs_ref, const Index index) -> void
	{
		visitedVertices[index] = true;

		for (const Vertex head : graph[index])
		{
			if (const Index headIndex = ToIndex(head, graph.size() / 2); !visitedVertices[headIndex])
			{
				dfs_ref(dfs_ref, headIndex);
			}
		}
		openTiles.push(ToVertex(index, graph.size() / 2));
	};

	// Runs dfs to get topological ordering.
	for (int i = 0; i < graph.size(); ++i)
	{
		if (!visitedVertices[i])
		{
			dfs(dfs, i);
		}
	}

	// Creating a transpose graph.
	Graph graphTranspose(graph.size());
	for (Index i = 0; i < graph.size(); ++i) { visitedVertices[i] = false; }

	for (Index i = 0; i < graph.size(); ++i)
	{
		for (const auto adjacentVertex : graph[i])
		{
			graphTranspose[ToIndex(adjacentVertex, graph.size() / 2)].push_back(ToVertex(i, graph.size() / 2));
		}
	}

	// Runs dfs on the transpose in topological order to get the strongly connected components.
	int id = 1;
	std::vector scc(graph.size(), 0);
	const auto getSCC = [&](const auto& getSCC_ref, const Vertex vertex) -> void
	{
		visitedVertices[ToIndex(vertex, graph.size() / 2)] = true;

		for (const Vertex head : graphTranspose[ToIndex(vertex, graph.size() / 2)])
		{
			if (!visitedVertices[ToIndex(head, graph.size() / 2)])
			{
				getSCC_ref(getSCC_ref, head);
			}
		}
		scc[ToIndex(vertex, graph.size() / 2)] = id;
	};

	while (!openTiles.empty())
	{
		const Vertex vertex = openTiles.top();
		openTiles.pop();

		if (!visitedVertices[ToIndex(vertex, graph.size() / 2)])
		{
			getSCC(getSCC, vertex);
			++id;
		}
	}

	// Checking if a boolean and its complement is in the same SCC.
	for (Index i = 0; i < graph.size() / 2; ++i)
	{
		if (scc[i] == scc[i + graph.size() / 2])
		{
			return false;
		}
	}

	return true;
}

int main()
{
	// Reading the file.
	std::cout << "Reading file...\r";
	std::ifstream inputFile{"../2SAT/CNF06.txt", std::ios::in};
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	// Generating the implication graph.
	uint32_t variables {0};
	inputFile >> variables;
	Graph graph(2 * variables);

	for (Vertex head {0}, tail {0}; inputFile >> head >> tail;)
	{
		graph[head > 0 ? variables + head - 1 : -head - 1].push_back(tail);
		graph[tail > 0 ? variables + tail - 1 : -tail - 1].push_back(head);
	}
	inputFile.close();
	std::cout << "Processing data...\r";

	std::cout << "Is CNF expression satisfiable: " << IsSatisfiable(graph) << "\n";

	std::cin.get();
	return 0;
}