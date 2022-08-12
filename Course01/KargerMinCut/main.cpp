/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/************************* Karger’s algorithm for Minimum Cut ****************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Vertex = uint32_t;
using Edge = std::pair<Vertex, Vertex>; // head, tail
using Graph = std::pair<Vertex, std::vector<Edge>>;

int KargerMinCut_Internal(Vertex vertices[], const uint64_t vertexCount, const Edge edges[], bool collapsedEdges[], const uint64_t edgeCount)
{
    for (int i = 0; i < vertexCount - 2;)
    {
        // Picking random edge to collapse.
        int randomIndex = rand() % edgeCount;
        while (collapsedEdges[randomIndex])
        {
            randomIndex = rand() % edgeCount;
        }

        // Collapsing the selected edge.
        collapsedEdges[randomIndex] = true;
        const Edge collapsedEdge = edges[randomIndex];

        const Vertex vertexToCollapse = vertices[collapsedEdge.second - 1];
        if (vertices[collapsedEdge.first - 1] == vertexToCollapse) { continue; }

        // Merging/Collapsing the vertex.
        for (int i = 0; i < vertexCount; i++)
        {
            if (vertices[i] == vertexToCollapse)
            {
                vertices[i] = vertices[collapsedEdge.first - 1];
            }
        }
        i++;
    }

    // Finding the edges that lies in between two groups.
    int minEdges = 0;
    for (int i = 0; i < edgeCount; i++)
    {
        if (vertices[edges[i].first - 1] != vertices[edges[i].second - 1])
        {
            minEdges++;
        }
    }
    return minEdges;
}

int KargerMinCut(const Graph& graph, const int iteration)
{
    int min = INT_MAX;
    const uint64_t edgeCount = graph.second.size();

    static auto* vertices = new Vertex[graph.first];
    static auto* collapsedEdges = new bool[edgeCount];

    for (int i = 0; i < iteration; i++)
    {
        for (uint64_t j = 0; j < edgeCount; j++) { collapsedEdges[j] = false; }
        for (uint64_t k = 0; k < graph.first; k++) { vertices[k] = k + 1; }

        if (const int current = KargerMinCut_Internal(vertices, graph.first, graph.second.data(), collapsedEdges, edgeCount);
            current < min)
        {
            min = current;
        }
    }

    delete[] collapsedEdges;
    delete[] vertices;
    return min;
}

int main()
{
    std::cout << "Reading file...\r";
    std::ifstream inputFile{ "../KargerMinCut/GraphData.txt", std::ios::in };
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open the file!\n";
        return -1;
    }

    uint64_t vertices{};
    std::vector<Edge> edges{};

    std::string line{};
    while (std::getline(inputFile, line))
    {
        std::istringstream lineStream{ line };
        Vertex head = 0;
        lineStream >> head;
        ++vertices;

        Vertex tail = 0;
        while (lineStream >> tail)
        {
            if (tail > head)
            {
                edges.emplace_back(Edge(head, tail));
            }
        }
    }
    inputFile.close();
    std::cout << "Processing Graph...\r";

    int minCut = KargerMinCut({ vertices, edges }, (int)vertices);
    std::cout << "Karger Min Cut Count -> " << minCut << "\n";
    std::cout << "Iterations: " << vertices << "\n";

    std::cin.get();
    return 0;
}