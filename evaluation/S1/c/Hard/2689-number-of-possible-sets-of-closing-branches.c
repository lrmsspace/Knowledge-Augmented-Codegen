// Source: https://leetcode.com/problems/number-of-possible-sets-of-closing-branches/   |   Difficulty: Hard
//
// Problem Description:
// There is a company with n branches across the country, some of which are connected by roads. Initially, all branches are reachable from each other by traveling some roads.
//
// The company has realized that they are spending an excessive amount of time traveling between their branches. As a result, they have decided to close down some of these branches (possibly none). However, they want to ensure that the remaining branches have a distance of at most maxDistance from each other.
//
// The distance between two branches is the minimum total traveled length needed to reach one branch from another.
//
// You are given integers n, maxDistance, and a 0-indexed 2D array roads, where roads[i] = [ui, vi, wi] represents the undirected road between branches ui and vi with length wi.
//
// Return the number of possible sets of closing branches, so that any branch has a distance of at most maxDistance from any other.
//
// Note that, after closing a branch, the company will no longer have access to any roads connected to it.
//
// Note that, multiple roads are allowed.
//
// Example:
// Input: n = 3, maxDistance = 5, roads = [[0,1,2],[1,2,10],[0,2,10]]
// Output: 5
// Explanation: The possible sets of closing branches are:
// - The set [2], after closing, active branches are [0,1] and they are reachable to each other within distance 2.
// - The set [0,1], after closing, the active branch is [2].
// - The set [1,2], after closing, the active branch is [0].
// - The set [0,2], after closing, the active branch is [1].
// - The set [0,1,2], after closing, there are no active branches.
// It can be proven, that there are only 5 possible sets of closing branches.
//
// Constraints:
// 1 <= n <= 10
// 	1 <= maxDistance <= 105
// 	0 <= roads.length <= 1000
// 	roads[i].length == 3
// 	0 <= ui, vi <= n - 1
// 	ui != vi
// 	1 <= wi <= 1000
// 	All branches are reachable from each other by traveling some roads.
//
// Helpful references (internal KB):
// - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
//   • When to use: Use when needing to find the shortest paths between all pairs of vertices in a weighted graph, especially if negative edge weights are present but no negative cycles.
//   • Idea: The Floyd-Warshall algorithm is a dynamic programming approach that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path lengths, achieving an O(N^3) time complexity.
//   • Invariants: After k iterations, d[i][j] stores the shortest path from i to j using only vertices {1, ..., k} as intermediate nodes.; d[i][j] always represents a valid path length or infinity, never an invalid negative value unless a negative cycle is detected.
//   • Tips: Initialize direct edge weights and infinity for non-existent edges.; Set distance from a vertex to itself to zero initially.
//   • Pitfalls: Incorrect loop order (k must be outermost) will yield incorrect results.; Improper handling of 'infinity' values can lead to overflow or incorrect comparisons.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Generating all K-combinations (bitset, recursion, enumeration)
//   • When to use: Use when an exhaustive list of all subsets of a specific size K from a set of N items is required. It's suitable for problems needing to explore every possible configuration of K elements.
//   • Idea: This algorithm systematically generates all unique subsets of size K from a set of N distinct elements, commonly employing recursion or bit manipulation. The typical time complexity is O(N choose K * K) for construction or O(N choose K) if just iterating.
//   • Invariants: The current partial combination always contains unique elements.; The number of elements chosen so far does not exceed K.
//   • Tips: Employ backtracking or recursion for a straightforward implementation.; Utilize bitmasks for efficient representation and generation, especially for smaller N.
//   • Pitfalls: Accidentally generating duplicate combinations if elements are not handled uniquely.; Failing to correctly define base cases or termination conditions for recursive calls.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfSets(int n, int maxDistance, int** roads, int roadsSize, int* roadsColSize) {
    /* Floyd-Warshall to find all-pairs shortest paths */
    int dist[10][10];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = (i == j) ? 0 : 1000000; /* infinity */

    for (int i = 0; i < roadsSize; ++i) {
        int u = roads[i][0], v = roads[i][1], w = roads[i][2];
        if (w < dist[u][v]) dist[u][v] = w;
        if (w < dist[v][u]) dist[v][u] = w;
    }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    /* Count valid subsets */
    int result = 0;
    int totalSubsets = 1 << n;
    for (int mask = 0; mask < totalSubsets; ++mask) {
        bool valid = true;
        for (int i = 0; i < n && valid; ++i) {
            if (!(mask & (1 << i))) continue; /* branch i is closed */
            for (int j = 0; j < n && valid; ++j) {
                if (!(mask & (1 << j))) continue; /* branch j is closed */
                if (dist[i][j] > maxDistance) {
                    valid = false;
                }
            }
        }
        if (valid) result++;
    }

    return result;      
}
