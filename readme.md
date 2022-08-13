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