#include "PCH.h"
#include "Graph.h"
#include "ClosestPair.h"

std::pair<Vec2Int, Vec2Int> ClosestPair::GetClosestPair(Vec2Int vertices[], const int start, const int end)
{
    const int size = end - start + 1;

    if(size < 4)
    {
        float minDistance = FLT_MAX;
        constexpr int largeNum = 9999;

        std::pair<Vec2Int, Vec2Int> closestPair({-largeNum, -largeNum}, {largeNum, largeNum});

        for (int i = 0; i < size; ++i)
        {
            for (int j = i + 1; j < size; ++j)
            {
                float current = GetDistance(vertices[i], vertices[j]);
                if (current < minDistance)
                {
                    minDistance = current;
                    closestPair = std::make_pair(vertices[i], vertices[j]);
                }
            }
        }
        return closestPair;
    }

    std::qsort(vertices, size, sizeof(Vec2Int),
       [](const void* a, const void* b) { return ((Vec2Int*)a)->x - ((Vec2Int*)b)->x; });

    const auto closestPairX = GetClosestPair(vertices, start, start + size / 2);
    const auto closestPairY = GetClosestPair(vertices, start + size / 2 + 1, end);

    const float minDisX = GetDistance(closestPairX);
    const float minDisY = GetDistance(closestPairY);

    const int dividerX = vertices[size/2].x;

    std::pair<Vec2Int, Vec2Int> closestPair = minDisX < minDisY ? closestPairX : closestPairY;
    float minDistance = GetDistance(closestPair);

    std::vector<Vec2Int> center;

    for(int i = 0; i < size; i++)
    {
        if((float)(vertices[i].x - dividerX) < minDistance)
        {
            center.push_back(vertices[i]);
        }
    }

    std::qsort(center.data(), center.size(), sizeof(Vec2Int),
        [](const void* a, const void* b) { return ((Vec2Int*)a)->y - ((Vec2Int*)b)->y; });

    for (int i = 0; i < center.size(); ++i)
    {
        for (int j = i + 1; j < center.size() && (float)(center[j].y - center[i].y) < minDistance; ++j)
        {
            const float current = GetDistance(center[i], center[j]);
            if (current < minDistance)
            {
                minDistance = current;
                closestPair = std::make_pair(center[i], center[j]);
            }
        }
    }

    return closestPair;
}

float ClosestPair::GetDistance(const Vec2Int& v1, const Vec2Int& v2)
{
    return sqrtf((float)((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y)));
}

float ClosestPair::GetDistance(const std::pair<Vec2Int, Vec2Int> pair)
{
    return GetDistance(pair.first, pair.second);
}