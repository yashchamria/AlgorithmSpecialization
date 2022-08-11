#pragma once

namespace Course01
{
	using Vertex = uint64_t;

	struct Vec2Int
	{
	public:
		int x, y;

	public:
		friend std::ostream& operator<< (std::ostream& out, const Vec2Int& vec);
	};

	inline std::ostream& operator<< (std::ostream& out, const Vec2Int& vec)
	{
		return out << "(" << vec.x << ", " << vec.y << ")";
	}

	struct Edge final
	{
	public:
		Edge(const Vertex head, const Vertex tail);

	public:
		Vertex head{};
		Vertex tail{};

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
}