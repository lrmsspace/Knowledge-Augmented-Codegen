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
// - Floyd-Warshall Algorithm (number, simulation)
//   • When to use: When you need to find the shortest paths between all possible pairs of vertices in a graph. It is particularly suitable for dense graphs or when negative edge weights are present, as long as no negative cycles are reachable.
//   • Idea: Floyd-Warshall is a dynamic programming algorithm that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path distances, achieving an O(V^3) time complexity.
//   • Invariants: After the k-th iteration, dist[i][j] contains the shortest path from i to j considering only vertices 0 to k-1 as intermediate nodes.; For any pair (i, j), dist[i][j] is always greater than or equal to the true shortest path distance from i to j (or infinity if unreachable).
//   • Tips: Initialize distances: direct edge weights, infinity for no direct edge, zero for self-loops.; The outermost loop must iterate through intermediate vertices (k).
//   • Pitfalls: Incorrect loop order (k not outermost) leads to incorrect results.; Integer overflow with large path sums if not using appropriate data types.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numberOfSets(int n, int maxDistance, int[][] roads) {
        // Step 1: Build the graph and compute shortest paths using Floyd-Warshall
        int[][] dist = new int[n][n];
        for (int i = 0; i < n; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE / 2); // Use a large value to avoid overflow
            dist[i][i] = 0;
        }
        for (int[] road : roads) {
            int u = road[0], v = road[1], w = road[2];
            dist[u][v] = Math.min(dist[u][v], w);
            dist[v][u] = Math.min(dist[v][u], w);
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // Step 2: Count valid subsets of branches to close
        int count = 0;
        int totalSubsets = 1 << n; // Total subsets of branches
        for (int mask = 0; mask < totalSubsets; mask++) {
            boolean valid = true;
            for (int i = 0; i < n && valid; i++) {
                if ((mask & (1 << i)) == 0) { // If branch i is not closed
                    for (int j = i + 1; j < n && valid; j++) {
                        if ((mask & (1 << j)) == 0) { // If branch j is not closed
                            if (dist[i][j] > maxDistance) {
                                valid = false;
                            }
                        }
                    }
                }
            }
            if (valid) {
                count++;
            }
        }

        return count;           
    }
}
