/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/************************************ Closest Pair ***************************************/

#include <iostream>
#include <vector>

using Coord = std::pair<int, int>;

inline std::ostream& operator<< (std::ostream& out, const Coord& coord)
{
    return out << "(" << coord.first << ", " << coord.second << ")";
}

float GetDistance(const Coord& v1, const Coord& v2)
{
    return sqrtf((float)((v1.first - v2.first) * (v1.first - v2.first) + (v1.second - v2.second) * (v1.second - v2.second)));
}

float GetDistance(const std::pair<Coord, Coord> pair)
{
    return GetDistance(pair.first, pair.second);
}

std::pair<Coord, Coord> GetClosestPair(Coord vertices[], const int start, const int end)
{
    const int size = end - start + 1;

    if (size < 4)
    {
        float minDistance = FLT_MAX;
        constexpr int largeNum = 9999;

        std::pair<Coord, Coord> closestPair({ -largeNum, -largeNum }, { largeNum, largeNum });

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

    std::qsort(vertices, size, sizeof(Coord),
        [](const void* a, const void* b) { return ((Coord*)a)->first - ((Coord*)b)->first; });

    const auto closestPairX = GetClosestPair(vertices, start, start + size / 2);
    const auto closestPairY = GetClosestPair(vertices, start + size / 2 + 1, end);

    const float minDisX = GetDistance(closestPairX);
    const float minDisY = GetDistance(closestPairY);

    const int dividerX = vertices[size / 2].first;

    std::pair<Coord, Coord> closestPair = minDisX < minDisY ? closestPairX : closestPairY;
    float minDistance = GetDistance(closestPair);

    std::vector<Coord> center;

    for (int i = 0; i < size; i++)
    {
        if ((float)(vertices[i].first - dividerX) < minDistance)
        {
            center.push_back(vertices[i]);
        }
    }

    std::qsort(center.data(), center.size(), sizeof(Coord),
        [](const void* a, const void* b) { return ((Coord*)a)->second - ((Coord*)b)->second; });

    for (int i = 0; i < center.size(); ++i)
    {
        for (int j = i + 1; j < center.size() && (float)(center[j].second - center[i].second) < minDistance; ++j)
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


int main()
{
    constexpr int vertexCount = 24;
    Coord vertices[vertexCount] =
    {
        {4, 7}, {6, 30}, {20, 0}, {50, 10}, {1, 10}, {66, 4},
        {19, 31}, {2, 90}, {4, 50}, {5, 1}, {12, 10}, {3, 4},
        {9, 23}, {1, 30}, {4, 35}, {65, 19}, {22, 7}, {8, 90},
        {2, 80}, {3, 30}, {0, 48}, {55, 98}, {82, 0}, {3, 24},
    };

    const auto closestPair = GetClosestPair(vertices, 0, vertexCount - 1);

    std::cout << "Closest Pair -> " << closestPair.first << ", " << closestPair.second << "\n";
    std::cout << "Distance -> " << GetDistance(closestPair) << "\n";

    std::cin.get();
    return 0;
}