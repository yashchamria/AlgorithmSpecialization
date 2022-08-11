#include "PCH.h"
#include "Graph.h"

namespace Course01
{
    Edge::Edge(const Vertex head, const Vertex tail) :
        head(head), tail(tail)
    {
    }

    Graph::Graph(const uint64_t vertices, const std::vector<Edge>& edges) :
        vertices(vertices), edges(edges)
    {
    }
}