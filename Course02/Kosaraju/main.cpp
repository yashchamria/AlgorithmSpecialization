/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/**************** Kosaraju's algorithm - strongly connected components *******************/

#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using Vertex = uint32_t;
using SCC = std::vector<Vertex>;

std::vector<std::vector<Vertex>> GetSCCs(const std::vector<Vertex> graph[], uint32_t vertexCount)
{
	std::vector visitedVertices(vertexCount, false);
	std::stack<Vertex> openTiles;

	const auto dfs = [&](auto const& dfs_ref, const Vertex vertex) -> void
	{
		visitedVertices[vertex - 1] = true;

		for (const Vertex index : graph[vertex - 1])
		{
			if (!visitedVertices[index - 1])
			{
				dfs_ref(dfs_ref, index);
			}
		}
		openTiles.push(vertex);
	};

	for (int i = 0; i < vertexCount; ++i)
	{
		if (!visitedVertices[i])
		{
			dfs(dfs, i + 1);
		}
	}

	for (int i = 0; i < vertexCount; ++i) { visitedVertices[i] = false; }
	const auto graphTranspose = new std::vector<Vertex>[vertexCount];

	for (int i = 0; i < vertexCount; ++i)
	{
		for (const auto adjacentVertex : graph[i])
		{
			graphTranspose[adjacentVertex - 1].push_back(i + 1);
		}
	}

	SCC scc;
	const auto getSCC = [&](auto const& getSCC_ref, const Vertex vertex) -> void
	{
		visitedVertices[vertex - 1] = true;

		for (const Vertex index : graphTranspose[vertex - 1])
		{
			if (!visitedVertices[index - 1])
			{
				getSCC_ref(getSCC_ref, index);
			}
		}
		scc.push_back(vertex);
	};

	std::vector<SCC> SCCs;
	while (!openTiles.empty())
	{
		const Vertex vertex = openTiles.top();
		openTiles.pop();

		if (!visitedVertices[vertex - 1])
		{
			getSCC(getSCC, vertex);
			SCCs.push_back(scc);
			scc.clear();
		}
	}

	return SCCs;
}

int main()
{
    // Required stack size - 4194304 ~ 4MB
	// Reading the file.
    std::cout << "Reading file...\r";
    std::ifstream inputFile{ "../Kosaraju/GraphData.txt", std::ios::in };
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open the file!\n";
        return -1;
    }

    constexpr Vertex vertexCount = 875714;
    auto graph = new std::vector<Vertex>[vertexCount];

    for (std::string line; std::getline(inputFile, line); )
    {
        std::istringstream lineStream{ line };
        Vertex head{ 0 }, tail{ 0 };
        lineStream >> head >> tail;
        graph[head - 1].push_back(tail);
    }
    inputFile.close();
    std::cout << "Processing Graph...\r";

	// Executing the algorithm.
    const auto& SCCs = GetSCCs(graph, vertexCount);

	// Outputting the data.
	std::priority_queue<Vertex> size{};
    for (const auto& scc : SCCs)
    {
        size.push(scc.size());
    }

    int i = 0;
    std::cout << "Ten largest SCCs size -> ";
    while (size.size() > 1 && i < 9)
    {
        std::cout << size.top() << ", ";
        size.pop();
        i++;
    }
	std::cout << size.top() << ".\n";

    std::cin.get();
    return 0;
}