This project contains algorithms I studied during Stanford's Algorithms Specialization on Coursera. Throughout the course, I will try to implement each algorithm and optional content as frequently as possible. Everything will be in C++. Premake5 is used to generate the project and Chrono is used to output the processing time.

Course 01 - Divide and Conquer, Sorting and Searching, and Randomized Algorithms:

Day 1: Implemented Karatsuba multiplication which runs in O(n^1.6) time compared to traditional multiplication's O(n^2) time. I used strings to store the large numbers.

Day 2: Implemented Merge sort and Inversion counting(number of pairs required to switch places to create a sorted array). Merge sort is a great example to demonstrate the power of divide and conquer. As it only takes O(nlogn) time compare to O(n^2) of the brute force approach.

Day 3: Implemented Quick sort algorithm, which sorts the data in O(nlogn) on average with no extra space requirement. Tested different pivots to split the array to measure the performance difference.

(Trying to speedrun some algorithms to cover the missed day.)

Day 5: Executed Karger's algorithm to find the minimum cut(least number of edges that disconnects the graph into two parts). It is a Monte Carlo algorithm and only produces accurate results 1/n^2 times, so the algorithm needs to be run around n times to produce a moderate result. But, it runs in (O(n^2)) to compare to alternates(O(n^5)).
Added QuickSelect(finds elements in an unsorted array for a given order). It is similar to quick sort but only takes O(n) time as it performs only one recursive call in each iteration with half the input size.
Implemented closest pair algorithm(to find the closest points on a graph). A very clever algorithm that utilizes sorting and divide and conquer to achieve O(nlogn^2) time.

Course 02 - Graph Search, Shortest Paths, and Data Structures:

Day 1: Implemented Kosaraju's algorithm to find the strongly connected components for a directed graph. The algorithm elegantly utilizes multiple DFS to achieve a running time of O(V+E).
Added Topological sort to find the linear transversal order for the vertices of a directed acyclic graph. This algorithm also relies on DFS and runs in O(V + E) time.

Day 2: Implemented Dijkstra's algorithm to find the shortest path. The implementation uses the min-heap to store the vertex distance making the lookup for minimum distance constant time. This approach gives the running time of O(ElogV).
Implemented a Median maintenance algorithm for an ongoing stream of data using multiple heaps in O(logn) running time.

Day 3: Implemented heap sort using heapify. The algorithm is similar to selection sort but instead of the linear search every iteration it maintains a max heap for constant lookup. The running time is O(nlogn).

Day 4: Solved the classic Two-sum problem for a range of targets using the hash tables.

Course 03 - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming:

Day 1: Implemented a greedy algorithm to schedule jobs in the most optimal way possible based on job priority and completion time. The running time is O(nlogn).
Implemented Prim's eager algorithm to find the minimum spanning tree using the min heap to store the vertex and the lowest edge cost to get there as the key. The running time is O(ElogV).

Day 2 : Implemented Kruskal's algorithm to find the minimum spanning tree using the blazingly fast union-find by rank data structure with path compression. This gives a running time of O(ElogV).
Similar to Kruskal, implemented a clustering algorithm for a graph based on the edge cost that relies on union-find data structure and runs in the same O(ElogE) time. Expanded the clustering algorithm to work with the large data set only expressed as hammering distance. Utilized hash tables for repeated lookups as sorting isn't viable.

Day 3 : Implemented Huffman Coding algorithm to achieve the lossless compression using the variable size bits to store the input based on their frequencies. The algorithm uses multiple queues and sorting to achieve O(nlogn) running time.

Day 4: Solved the weighted independent sum problem for a path graph using the dynamic programming paradigm and memoization to achieve a linear time of O(n).

Day 7: Implemented 0/1 Knapsack algorithm to find the maximum value subset of items for a given capacity. The algorithm uses the dynamic programming paradigm to achieve the solution in O(nw) running time.