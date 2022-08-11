#pragma once
#include "Graph.h"

namespace Course01
{
	using VertexGroup = int;

	class MinCut
	{
	public:
		static int KargerMinCut(const Graph& graph, const int iteration);

	private:
		static int KargerMinCut_Internal(Vertex vertices[], const uint64_t vertexCount, const Edge edges[], bool collapsedEdges[], const uint64_t edgeCount);
	};
}