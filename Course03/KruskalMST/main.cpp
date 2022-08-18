/******************************************************************************************
********** Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming *************
******************************************************************************************/

/***************** Kruskal's algorithm to find the minimum spanning tree ********************/

#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <ranges>
#include <vector>

using Vertex = uint32_t;
using Cost = int32_t;
using Edge = std::tuple<Vertex, Vertex, Cost>;
using Graph = std::pair<Vertex, std::vector<Edge>>;
using SpanningTree = std::vector<Edge>;

struct UnionFind
{
	using Parent = uint32_t;
	using Rank = uint32_t;
	using Index = uint32_t;
	using Node = std::pair<Parent, Rank>;

private:
	Node* m_nodes;

public:
	explicit UnionFind(const Index nodeCount) : m_nodes(new Node[nodeCount])
	{
		for (Index i = 0; i < nodeCount; ++i)
		{
			m_nodes[i] = { i, 0 };
		}
	}

	bool Union(const Index index1, const Index index2) const // Returns false if both the nodes are in same group.
	{
		const Index group1 = CollapseFind(index1);
		const Index group2 = CollapseFind(index2);

		if(group1 == group2) { return false; }

		if(m_nodes[group1].second < m_nodes[group2].second) // Comparing higher ranks.
		{
			m_nodes[group1].first = m_nodes[group2].first;
			++m_nodes[group2].second;
		}
		else
		{
			m_nodes[group2].first = m_nodes[group1].first;
			++m_nodes[group1].second;
		}
		return true;
	}

	[[nodiscard]] Index CollapseFind(const Index index) const
	{
		if(m_nodes[index].first == index)
		{
			return index;
		}
		return m_nodes[index].first = CollapseFind(m_nodes[index].first);
	}
};

SpanningTree GetMinimumSpanningTree(Graph& graph)
{
	std::ranges::sort(graph.second, [](const Edge& edge1, const Edge& edge2) { return std::get<2>(edge1) < std::get<2>(edge2); });
	const UnionFind clusters(graph.first);

	SpanningTree mst;
	mst.reserve(graph.first - 1);


	for(const Edge& edge : graph.second)
	{
		if(clusters.Union(std::get<0>(edge), std::get<1>(edge)))
		{
			mst.emplace_back(edge);
		}

		if (mst.size() == graph.first - 1) { break; }
	}

	return mst;
}

int main()
{
	// Reading the file.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../KruskalMST/GraphData.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	uint32_t vertexCount {0}, edgeCount{0};
	inputFile >> vertexCount >> edgeCount;
	Graph graph;
	graph.first = vertexCount;
	graph.second.reserve(edgeCount);

	for (Edge edge; inputFile >> std::get<0>(edge) >> std::get<1>(edge) >> std::get<2>(edge);)
	{
		graph.second.emplace_back(--std::get<0>(edge), --std::get<1>(edge), std::get<2>(edge));
	}
	inputFile.close();

	const auto& mst = GetMinimumSpanningTree(graph);

	std::cout << "Minimum spanning tree cost: " <<
		std::accumulate(mst.cbegin(), mst.cend(), 0, [](int sum, const auto& edge) { return sum + std::get<2>(edge); });

	std::cin.get();
    return 0;
}