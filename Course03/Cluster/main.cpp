/******************************************************************************************
********** Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming *************
******************************************************************************************/

/******************************** Clustering algorithm ***********************************/

#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>

using Vertex = uint32_t;
using Cost = int32_t;
using Edge = std::tuple<Vertex, Vertex, Cost>;
using Graph = std::pair<Vertex, std::vector<Edge>>;

struct UnionFind
{
	using Parent = uint32_t;
	using Rank = uint32_t;
	using Index = uint32_t;
	using Node = std::pair<Parent, Rank>;
	using Cluster = std::vector<Index>;

private:
	Node* m_nodes;
	Index m_size;
	Index m_clusterCount;

public:
	explicit UnionFind(const Index nodeCount) : m_nodes(new Node[nodeCount]), m_size(nodeCount), m_clusterCount(nodeCount)
	{
		for (Index i = 0; i < nodeCount; ++i)
		{
			m_nodes[i] = { i, 0 };
		}
	}

	bool Union(const Index index1, const Index index2) // Returns false if both the nodes are in same group.
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
		--m_clusterCount;
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

	[[nodiscard]] bool IsDisjoint(const Index index1, const Index index2) const
	{
		return CollapseFind(index1) != CollapseFind(index2);
	}

	[[nodiscard]] std::vector<Cluster> GetClusters() const
	{
		std::unordered_map<Index, Index> leaderIndexMap;
		std::vector<Cluster> clusters;

		for(Index i = 0; i < m_size; ++i)
		{
			const Index leader = CollapseFind(i);
			if(leaderIndexMap.contains(leader))
			{
				clusters[leaderIndexMap[leader]].push_back(i);
			}
			else
			{
				leaderIndexMap[leader] = clusters.size();
				clusters.push_back({i});
			}
		}

		return clusters;
	}

	[[nodiscard]] Index GetClusterCount() const { return m_clusterCount; }
};

UnionFind GetClusters(Graph& graph, const uint32_t& clusterCount)
{
	UnionFind clusters(graph.first);
	std::ranges::sort(graph.second, [](const Edge& edge1, const Edge& edge2) { return std::get<2>(edge1) < std::get<2>(edge2); });

	for (const Edge& edge : graph.second)
	{
		if (clusters.GetClusterCount() > clusterCount)
		{
			clusters.Union(std::get<0>(edge), std::get<1>(edge));
		}
	}
	return clusters;
}

int main()
{
	// Reading the file.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../Cluster/GraphData.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

	uint32_t vertexCount {0};
	inputFile >> vertexCount;
	Graph graph;
	graph.first = vertexCount;

	for (Edge edge; inputFile >> std::get<0>(edge) >> std::get<1>(edge) >> std::get<2>(edge);)
	{
		graph.second.emplace_back(--std::get<0>(edge), --std::get<1>(edge), std::get<2>(edge));
	}
	inputFile.close();

	const auto& clusters = GetClusters(graph, 4);

	for (const Edge& edge : graph.second) // Edges are already in the sorted order.
	{
		if(clusters.IsDisjoint(std::get<0>(edge), std::get<1>(edge)))
		{
			std::cout << "Maximum spacing between the clusters: " << std::get<2>(edge);
			break;
		}
	}

	std::cin.get();
    return 0;
}