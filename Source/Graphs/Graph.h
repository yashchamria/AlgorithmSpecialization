#pragma once

using Vertex = uint64_t;

struct Edge final
{
public:
	Edge(const Vertex head, const Vertex tail);

public:
	Vertex head {};
	Vertex tail {};

public:
	bool operator== (const Edge& other) const
	{
		return head == other.head && tail == other.tail;
	}

	bool operator!= (const Edge& other) const
	{
		return !operator==(other);
	}
};

struct Graph final
{
public:
	Graph(const uint64_t vertices, const std::vector<Edge>& edges);

public:
	const uint64_t vertices;
	const std::vector<Edge> edges;
};