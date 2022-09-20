/******************************************************************************************
******** Shortest Paths Revisited, NP-Complete Problems and What To Do About Them *********
******************************************************************************************/

/*********************** Ford-Fulkerson maximum flow algorithm ***************************/

#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

using Vertex = uint32_t;
using Capacity = uint32_t;

using Edge = std::pair<Vertex, Vertex>;
using Path = std::vector<Vertex>;
using Graph = std::vector<std::vector<Capacity>>;

std::pair<Path, Capacity> GetPathAndItsMaxCapacity(const Graph& graph, const Vertex& start, const Vertex& end)
{
	Path visitSequence {};
	std::vector visited(graph.size(), false);

	bool bReached {false};
	const auto dfs = [&](auto const& dfs_ref, const Vertex& vertex) -> void
	{
		if (vertex == end) { bReached = true; }
		visited[vertex] = true;

		for (Vertex head = 0; head < graph.size(); ++head)
		{
			if (bReached) { break; }

			if (!visited[head] && graph[vertex][head] != 0)
			{
				dfs_ref(dfs_ref, head);
			}
		}
		visitSequence.push_back(vertex);
	};

	dfs(dfs, start);

	Path path {};
	Capacity bottleNeck {std::numeric_limits<Capacity>::max()};

	for (int i = visitSequence.size() - 1; i > 0; --i)
	{
		path.push_back(visitSequence[i]);

		if (const Capacity capacity = graph[visitSequence[i]][visitSequence[i - 1]]; capacity < bottleNeck)
		{
			bottleNeck = capacity;
		}

		if (visitSequence[i - 1] == end)
		{
			path.push_back(visitSequence[i - 1]);
			return { path, bottleNeck };
		}
	}

	return {};
}

Graph GetMaxFlow(Graph residualGraph, const Vertex& source, const Vertex& sink)
{
	auto path = GetPathAndItsMaxCapacity(residualGraph, source, sink);

	while(!path.first.empty())
	{
		for (int i = 0; i < path.first.size() - 1; ++i)
		{
			// Pushes the flow forward reducing the capacity.
			residualGraph[path.first[i]][path.first[i + 1]] -= path.second;

			// Creating reverse edges to undo the flow if required.
			residualGraph[path.first[i + 1]][path.first[i]] += path.second;
		}

		path = GetPathAndItsMaxCapacity(residualGraph, source, sink);
	}

	return residualGraph;
}

std::vector<Edge> GetMinCut(const Graph& graph, const Graph& residualGraph, const Vertex& source, const Vertex& sink)
{
	std::vector visited(residualGraph.size(), false);

	const auto dfs = [&](auto const& dfs_ref, const Vertex& vertex) -> void
	{
		visited[vertex] = true;

		for (Vertex head = 0; head < residualGraph.size(); ++head)
		{
			if (!visited[head] && residualGraph[vertex][head] != 0)
			{
				dfs_ref(dfs_ref, head);
			}
		}
	};

	dfs(dfs, source);

	std::vector<Edge> minCut;

	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph.size(); j++)
		{
			if (visited[i] && !visited[j] && graph[i][j])
			{
				minCut.emplace_back(i, j);
				
			}
		}
	}
	return minCut;
}

int main()
{
	/*********************************************************
			          1 ---- c3 ----> 2        
			        / |              / \       
	 		      c5  |            /    c6     
			    /     |          /         \   
			0->      c1       c2            ->5
			    \     |      /             /   
			      c3  |    /            c3     
			        \ |  /             /       
			          3 ---- c4 ----> 4        
	 **********************************************************/

	//constexpr Vertex source {0}, sink {5};
	//const Graph capacityGraph
	//{
	//	//{0, 1, 2, 3, 4, 5}
	//	{0, 5, 0, 3, 0, 0},  // -> 0
	//	{0, 0, 3, 1, 0, 0},  // -> 1
	//	{0, 0, 0, 2, 0, 6},  // -> 2
	//	{0, 0, 0, 0, 4, 0},  // -> 3
	//	{0, 0, 0, 0, 0, 3},  // -> 4
	//	{0, 0, 0, 0, 0, 0},  // -> 5
	//};

	/*********************************************************
			          1 ---- c6 ----> 3 ---- c5 ----> 7
			        / |              / \               \
			      c9  |            /    c6              c6
			    /     |          /         \              \
			0->       c3       c2           ->4 --- c6 --- ->8
			    \     |      /             /              /
			      c8  |    /            c6               c3
			        \ |  /             /               /
			          2 ---- c7 ----> 5 ---- c3 ----> 9
			            \                          /
			               \                    /
			                  c3            c4
			                     \       /
			                         6
	**********************************************************/

	constexpr Vertex source {0}, sink {8};
	const Graph capacityGraph
	{
		//{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
		{0, 9, 9, 0, 0, 0, 0, 0, 0, 0},  // -> 0
		{0, 0, 3, 6, 0, 0, 0, 0, 0, 0},  // -> 1
		{0, 0, 0, 0, 0, 7, 3, 0, 0, 0},  // -> 2
		{0, 0, 2, 0, 6, 0, 0, 5, 0, 0},  // -> 3
		{0, 0, 0, 0, 0, 0, 0, 0, 6, 0},  // -> 4
		{0, 0, 0, 0, 6, 0, 0, 0, 0, 3},  // -> 5
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 4},  // -> 6
		{0, 0, 0, 0, 0, 0, 0, 0, 6, 0},  // -> 7
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // -> 8
		{0, 0, 0, 0, 0, 0, 0, 0, 3, 0},  // -> 9

	};

	const auto residualGraph = GetMaxFlow(capacityGraph, source, sink);

	const Capacity maxFlow = std::accumulate(residualGraph[sink].cbegin(), residualGraph[sink].cend(), 0);
	std::cout << "Maximum flow: " << maxFlow << "\n";

	const auto minCut = GetMinCut(capacityGraph, residualGraph, source, sink);

	std::cout << "Minimum cut edges: ";
	for(int i = 0; i < minCut.size(); ++i)
	{
		std::cout << "(" << minCut[i].first << ", " << minCut[i].second << ", c" << capacityGraph[minCut[i].first][minCut[i].second] <<
			(i != minCut.size() - 1 ? "), " : ").\n");
	}
	std::cin.get();
	return 0;
}