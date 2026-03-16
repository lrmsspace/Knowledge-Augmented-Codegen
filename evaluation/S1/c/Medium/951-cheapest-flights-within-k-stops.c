// Source: https://leetcode.com/problems/cheapest-flights-within-k-stops/   |   Difficulty: Medium
//
// Problem Description:
// There are n cities connected by some number of flights. You are given an array flights where flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.
//
// You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.
//
// Example:
// Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
// Output: 700
// Explanation:
// The graph is shown above.
// The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
// Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
//
// Constraints:
// 1 <= n <= 100
// 	0 <= flights.length <= (n * (n - 1) / 2)
// 	flights[i].length == 3
// 	0 <= fromi, toi < n
// 	fromi != toi
// 	1 <= pricei <= 104
// 	There will not be any multiple flights between two cities.
// 	0 <= src, dst, k < n
// 	src != dst
//
// Helpful references (internal KB):
// - Bellman-Ford Algorithm (graph, array, bellman-ford)
//   • When to use: Use when finding single-source shortest paths in a weighted graph that may contain negative edge weights. It is also essential for detecting and identifying negative cycles reachable from the source.
//   • Idea: The Bellman-Ford algorithm iteratively relaxes all edges in a graph V-1 times to find single-source shortest paths, correctly handling negative edge weights. It runs in O(V*E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: After k iterations, dist[u] holds the shortest path distance from source to u using at most k edges.; dist[u] always represents an upper bound on the true shortest path distance from the source to u.
//   • Tips: Initialize source distance to 0 and all other distances to infinity.; Perform V-1 iterations, relaxing all edges in each iteration.
//   • Pitfalls: Does not work if shortest paths are required in the presence of negative cycles (distances become -infinity).; Forgetting to properly initialize distances can lead to incorrect results.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Minimum-cost flow - Successive shortest path algorithm (graph, array, number, greedy, dijkstra, bellman-ford)
//   • When to use: When you need to find a flow of a certain amount (or maximum possible flow) through a network while minimizing the total cost associated with sending flow along edges. It is suitable for problems involving resource allocation with varying costs.
//   • Idea: The successive shortest path algorithm finds a minimum-cost flow by repeatedly finding a shortest augmenting path in the residual graph and pushing flow along it. Its complexity depends on the shortest path algorithm used (Bellman-Ford for general costs, Dijkstra with potentials for non-negative residual costs).
//   • Invariants: At the start of each iteration, the current flow is a valid flow from source to sink.; The residual graph correctly represents remaining capacities and reverse edges for the current flow.
//   • Tips: Use potentials (reduced costs) with Dijkstra to efficiently handle non-negative edge costs in the residual graph.; Initialize potentials to zero and update them after each shortest path computation.
//   • Pitfalls: Incorrectly updating residual capacities or reverse edge costs can lead to wrong results.; Failing to use potentials with Dijkstra can lead to incorrect shortest paths in graphs with negative edges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int k) {
    int dist[n];
    for (int i = 0; i < n; i++) {
        dist[i] = 1000000000; // Use a large number to represent infinity
    }
    dist[src] = 0;

    for (int i = 0; i <= k; i++) {
        int tempDist[n];
        for (int j = 0; j < n; j++) {
            tempDist[j] = dist[j];
        }

        for (int j = 0; j < flightsSize; j++) {
            int from = flights[j][0];
            int to = flights[j][1];
            int price = flights[j][2];

            if (dist[from] + price < tempDist[to]) {
                tempDist[to] = dist[from] + price;
            }
        }

        for (int j = 0; j < n; j++) {
            dist[j] = tempDist[j];
        }
    }

    return dist[dst] == 1000000000 ? -1 : dist[dst];        
}
