#pragma once

struct Vec2Int;

class ClosestPair final
{
public:
    static std::pair<Vec2Int, Vec2Int> GetClosestPair(Vec2Int vertices[], const int start, const int end);

public:
    inline static float GetDistance(const Vec2Int& v1, const Vec2Int& v2);
    inline static float GetDistance(const std::pair<Vec2Int, Vec2Int> pair);
};