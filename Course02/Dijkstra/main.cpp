/******************************************************************************************
******************* Graph Search, Shortest Paths, and Data Structures *********************
******************************************************************************************/

/******************** Dijkstra algorithm to find the shortest path ***********************/

#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using Vertex = uint32_t;
using Distance = uint32_t;
using AdjacentEdges = std::vector<std::pair<Vertex, Distance>>;
using Graph = std::vector<AdjacentEdges>;

constexpr auto MaxDistance = 1000000;

std::vector<Distance> GetShortestPath(const Graph& graph, const Vertex& startVertex)
{
	std::priority_queue<std::pair<Distance, Vertex>, std::vector<std::pair<Distance, Vertex>>, std::greater<>> openTiles;
	std::vector<Distance> minDistance(graph.size(), MaxDistance);

	openTiles.emplace(0, startVertex);
	minDistance[startVertex - 1] = 0;

	while(!openTiles.empty())
	{
		const Vertex visitingVertex = openTiles.top().second;
		openTiles.pop();

		for (const auto& adjacentVertex : graph[visitingVertex - 1])
		{
			const Distance distance = minDistance[visitingVertex - 1] + adjacentVertex.second;

			if (distance < minDistance[adjacentVertex.first - 1])
			{
				minDistance[adjacentVertex.first - 1] = distance;
				openTiles.emplace(distance, adjacentVertex.first);
			}
		}
	}

	return minDistance;
}

int main()
{
	// Reading the file.
	std::cout << "Reading data...\r";
	std::ifstream inputFile{ "../Dijkstra/GraphData.txt", std::ios::in };
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open the file!\n";
		return -1;
	}

    Graph graph(200);

	for (std::string line; std::getline(inputFile, line); )
	{
		std::istringstream lineStream {line};
		Vertex head {0}, tail {0};
		Distance distance {MaxDistance};
		char comma = ',';
		lineStream >> tail;

		while(lineStream >> head >> comma >> distance)
		{
			graph[tail - 1].emplace_back(head, distance);
		}
	}
	inputFile.close();
	std::cout << "Processing data...\r";

	const auto& minDistance = GetShortestPath(graph, 1);

	std::cout << "Min Distance from:\n";

	for (int i = 0; i < minDistance.size(); ++i)
	{
		std::cout << "1 -> " << i + 1 << " = " << minDistance[i] << "\n";
	}

	std::cin.get();
    return 0;
}

/*
1 -> 1 = 0
1 -> 2 = 2971
1 -> 3 = 2644
1 -> 4 = 3056
1 -> 5 = 2525
1 -> 6 = 2818
1 -> 7 = 2599
1 -> 8 = 1875
1 -> 9 = 745
1 -> 10 = 3205
1 -> 11 = 1551
1 -> 12 = 2906
1 -> 13 = 2394
1 -> 14 = 1803
1 -> 15 = 2942
1 -> 16 = 1837
1 -> 17 = 3111
1 -> 18 = 2284
1 -> 19 = 1044
1 -> 20 = 2351
1 -> 21 = 3630
1 -> 22 = 4028
1 -> 23 = 2650
1 -> 24 = 3653
1 -> 25 = 2249
1 -> 26 = 2150
1 -> 27 = 1222
1 -> 28 = 2090
1 -> 29 = 3540
1 -> 30 = 2303
1 -> 31 = 3455
1 -> 32 = 3004
1 -> 33 = 2551
1 -> 34 = 2656
1 -> 35 = 998
1 -> 36 = 2236
1 -> 37 = 2610
1 -> 38 = 3548
1 -> 39 = 1851
1 -> 40 = 4091
1 -> 41 = 2732
1 -> 42 = 2040
1 -> 43 = 3312
1 -> 44 = 2142
1 -> 45 = 3438
1 -> 46 = 2937
1 -> 47 = 2979
1 -> 48 = 2757
1 -> 49 = 2437
1 -> 50 = 3152
1 -> 51 = 2503
1 -> 52 = 2817
1 -> 53 = 2420
1 -> 54 = 3369
1 -> 55 = 2862
1 -> 56 = 2609
1 -> 57 = 2857
1 -> 58 = 3668
1 -> 59 = 2947
1 -> 60 = 2592
1 -> 61 = 1676
1 -> 62 = 2573
1 -> 63 = 2498
1 -> 64 = 2047
1 -> 65 = 826
1 -> 66 = 3393
1 -> 67 = 2535
1 -> 68 = 4636
1 -> 69 = 3650
1 -> 70 = 743
1 -> 71 = 1265
1 -> 72 = 1539
1 -> 73 = 3007
1 -> 74 = 4286
1 -> 75 = 2720
1 -> 76 = 3220
1 -> 77 = 2298
1 -> 78 = 2795
1 -> 79 = 2806
1 -> 80 = 982
1 -> 81 = 2976
1 -> 82 = 2052
1 -> 83 = 3997
1 -> 84 = 2656
1 -> 85 = 1193
1 -> 86 = 2461
1 -> 87 = 1608
1 -> 88 = 3046
1 -> 89 = 3261
1 -> 90 = 2018
1 -> 91 = 2786
1 -> 92 = 647
1 -> 93 = 3542
1 -> 94 = 3415
1 -> 95 = 2186
1 -> 96 = 2398
1 -> 97 = 4248
1 -> 98 = 3515
1 -> 99 = 2367
1 -> 100 = 2970
1 -> 101 = 3536
1 -> 102 = 2478
1 -> 103 = 1826
1 -> 104 = 2551
1 -> 105 = 3368
1 -> 106 = 2303
1 -> 107 = 2540
1 -> 108 = 1169
1 -> 109 = 3140
1 -> 110 = 2317
1 -> 111 = 2535
1 -> 112 = 1759
1 -> 113 = 1899
1 -> 114 = 508
1 -> 115 = 2399
1 -> 116 = 3513
1 -> 117 = 2597
1 -> 118 = 2176
1 -> 119 = 1090
1 -> 120 = 2328
1 -> 121 = 2818
1 -> 122 = 1306
1 -> 123 = 2805
1 -> 124 = 2057
1 -> 125 = 2618
1 -> 126 = 1694
1 -> 127 = 3285
1 -> 128 = 1203
1 -> 129 = 676
1 -> 130 = 1820
1 -> 131 = 1445
1 -> 132 = 2468
1 -> 133 = 2029
1 -> 134 = 1257
1 -> 135 = 1533
1 -> 136 = 2417
1 -> 137 = 3599
1 -> 138 = 2494
1 -> 139 = 4101
1 -> 140 = 546
1 -> 141 = 1889
1 -> 142 = 2616
1 -> 143 = 2141
1 -> 144 = 2359
1 -> 145 = 648
1 -> 146 = 2682
1 -> 147 = 3464
1 -> 148 = 2873
1 -> 149 = 3109
1 -> 150 = 2183
1 -> 151 = 4159
1 -> 152 = 1832
1 -> 153 = 2080
1 -> 154 = 1831
1 -> 155 = 2001
1 -> 156 = 3013
1 -> 157 = 2143
1 -> 158 = 1376
1 -> 159 = 1627
1 -> 160 = 2403
1 -> 161 = 4772
1 -> 162 = 2556
1 -> 163 = 2124
1 -> 164 = 1693
1 -> 165 = 2442
1 -> 166 = 3814
1 -> 167 = 2630
1 -> 168 = 2038
1 -> 169 = 2776
1 -> 170 = 1365
1 -> 171 = 3929
1 -> 172 = 1990
1 -> 173 = 2069
1 -> 174 = 3558
1 -> 175 = 1432
1 -> 176 = 2279
1 -> 177 = 3829
1 -> 178 = 2435
1 -> 179 = 3691
1 -> 180 = 3027
1 -> 181 = 2345
1 -> 182 = 3807
1 -> 183 = 2145
1 -> 184 = 2703
1 -> 185 = 2884
1 -> 186 = 3806
1 -> 187 = 1151
1 -> 188 = 2505
1 -> 189 = 2340
1 -> 190 = 2596
1 -> 191 = 4123
1 -> 192 = 1737
1 -> 193 = 3136
1 -> 194 = 1073
1 -> 195 = 1707
1 -> 196 = 2417
1 -> 197 = 3068
1 -> 198 = 1724
1 -> 199 = 815
1 -> 200 = 2060
 */