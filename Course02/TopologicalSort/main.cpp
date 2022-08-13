/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/**************** Topological sort for directed acyclic graphs *******************/

#include <iostream>
#include <stack>
#include <vector>

using Vertex = uint32_t;
using DirectedEdges = std::vector<Vertex>; // heads.
using Graph = std::vector<DirectedEdges>;

std::stack<Vertex> GetTopologicalSort(const Graph& graph)
{
	std::vector visitedVertices(graph.size(), false);
	std::stack<Vertex> topSorted;

	const auto dfs = [&](auto const& dfs_ref, const Vertex vertex) -> void
	{
		visitedVertices[vertex] = true;

		for (const auto& vertex : graph[vertex])
		{
			if (!visitedVertices[vertex])
			{
				dfs_ref(dfs_ref, vertex);
			}
		}
		topSorted.push(vertex);
	};

	for (int i = 0; i < graph.size(); i++)
	{
		if(!visitedVertices[i])
		{
			dfs(dfs, i);
		}
	}

	return topSorted;
}

int main()
{
    const Graph graph({{3},{3}, {0, 1}, {6, 7}, {0, 3, 5}, {9, 10}, {8}, {8, 9}, {11}, {11, 12}, {9}, {}, {}});

	auto topSort = GetTopologicalSort(graph);

    std::cout << "Topological Order -> ";
	while(!topSort.empty())
	{
		std::cout << topSort.top() << (topSort.size() > 1 ? ", " : ".");
		topSort.pop();
	}

    std::cin.get();
    return 0;
}