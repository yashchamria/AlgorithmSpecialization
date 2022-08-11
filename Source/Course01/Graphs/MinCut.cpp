#include "PCH.h"
#include "MinCut.h"
#include "Graph.h"

namespace Course01
{
    int MinCut::KargerMinCut_Internal(Vertex vertices[], const uint64_t vertexCount, const Edge edges[], bool collapsedEdges[], const uint64_t edgeCount)
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

            const Vertex vertexToCollapse = vertices[collapsedEdge.tail - 1];
            if (vertices[collapsedEdge.head - 1] == vertexToCollapse) { continue; }

            // Merging/Collapsing the vertex.
            for (int i = 0; i < vertexCount; i++)
            {
                if (vertices[i] == vertexToCollapse)
                {
                    vertices[i] = vertices[collapsedEdge.head - 1];
                }
            }
            i++;
        }

        // Finding the edges that lies in between two groups.
        int minEdges = 0;
        for (int i = 0; i < edgeCount; i++)
        {
            if (vertices[edges[i].head - 1] != vertices[edges[i].tail - 1])
            {
                minEdges++;
            }
        }
        return minEdges;
    }

    int MinCut::KargerMinCut(const Graph& graph, const int iteration)
    {
        int min = INT_MAX;
        const uint64_t edgeCount = graph.edges.size();

        static auto* vertices = new Vertex[graph.vertices];
        static auto* collapsedEdges = new bool[edgeCount];

        for (int i = 0; i < iteration; i++)
        {
            for (uint64_t j = 0; j < edgeCount; j++) { collapsedEdges[j] = false; }
            for (uint64_t k = 0; k < graph.vertices; k++) { vertices[k] = k + 1; }

            if (const int current = KargerMinCut_Internal(vertices, graph.vertices, &graph.edges[0], collapsedEdges, edgeCount);
                current < min)
            {
                min = current;
            }
        }

        delete[] collapsedEdges;
        delete[] vertices;
        return min;
    }
}