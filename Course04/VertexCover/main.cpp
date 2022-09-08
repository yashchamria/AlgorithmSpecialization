/******************************************************************************************
******** Shortest Paths Revisited, NP-Complete Problems and What To Do About Them *********
******************************************************************************************/

/****************************** Vertex Cover problem ***********************************/

#include <algorithm>
#include <iostream>
#include <vector>

using Vertex = uint32_t;
using Edge = std::pair<Vertex, Vertex>;
using Graph = std::vector<Edge>;
using VertexCover = std::vector<Vertex>;

VertexCover GetVertexCover(const Graph& graph, const Vertex coverSize)
{
	if (coverSize < 1 || graph.empty()) { return {}; }

	const auto getSubVertexCover = [&](const Vertex& vertex) -> VertexCover
	{
		Graph subGraph = graph;
		std::erase_if(subGraph, [&](const auto& edge) { return edge.first == vertex || edge.second == vertex; });

		if (subGraph.empty()) { return { vertex }; }

		if (VertexCover cover = GetVertexCover(subGraph, coverSize - 1); !cover.empty())
		{
			cover.push_back(vertex);
			return cover;
		}

		return {};
	};

	VertexCover cover = getSubVertexCover(graph[0].first);
	return !cover.empty() ? cover : getSubVertexCover(graph[0].second);
}

int main()
{
	/*********************************************************
		2 --- 3 --- 4 --- 7 --- 14     15     18 --- 22
		|     |    |        \      \   |    / |      | 
		|     |    |          \      \ |  /   |      | 
		1     5 --- 6 --- 8     12 --- 13 --- 17     21
		       \   /      |      | \          |  \   | 
		        \ /       |      |   \        |    \ | 
		         9        10 --- 11    16 --- 19 --- 20
		                            \           \   /  
		                              \          \ /   
		                                23 ------ 24   
	**********************************************************/

	const Graph graph
	{
		{1, 2}, {2, 3}, {3, 4}, {3, 5}, {4, 5}, {4, 6}, {4, 7}, {5, 6},
		{5, 9}, {6, 8}, {6, 9}, {7, 12}, {7, 14}, {8, 10}, {10, 11},
		{11, 12}, {11, 23}, {12, 13}, {12, 16}, {13, 14}, {13, 15}, {13, 17},
		{13, 18}, {16, 19}, {17, 18}, {17, 19}, {17, 20}, {18, 22}, {19, 20},
		{19, 24}, {20, 21}, {20, 24}, {21, 22}, {23, 24}
	};

	VertexCover vertexCover{};
	Vertex coverSize {1};
	while(vertexCover.empty()) { vertexCover = GetVertexCover(graph, coverSize++); }
	std::ranges::sort(vertexCover);

	if (!vertexCover.empty())
	{
		std::cout << "Vertex Cover Size: " << vertexCover.size() << "\nVertex Cover: { ";
		for (int i = 0; i < vertexCover.size(); ++i)
		{
			std::cout << vertexCover[i] << (i == vertexCover.size() - 1 ? " }\n" : ", ");
		}
	}
	else
	{
		std::cout << "Vertex Cover of size " << coverSize << " doesn't exist.\n";
	}

	std::cin.get();
	return 0;
}