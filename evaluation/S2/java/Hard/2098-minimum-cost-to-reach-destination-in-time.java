// Source: https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/   |   Difficulty: Hard
//
// Problem Description:
// There is a country of n cities numbered from 0 to n - 1 where all the cities are connected by bi-directional roads. The roads are represented as a 2D integer array edges where edges[i] = [xi, yi, timei] denotes a road between cities xi and yi that takes timei minutes to travel. There may be multiple roads of differing travel times connecting the same two cities, but no road connects a city to itself.
//
// Each time you pass through a city, you must pay a passing fee. This is represented as a 0-indexed integer array passingFees of length n where passingFees[j] is the amount of dollars you must pay when you pass through city j.
//
// In the beginning, you are at city 0 and want to reach city n - 1 in maxTime minutes or less. The cost of your journey is the summation of passing fees for each city that you passed through at some moment of your journey (including the source and destination cities).
//
// Given maxTime, edges, and passingFees, return the minimum cost to complete your journey, or -1 if you cannot complete it within maxTime minutes.
//
// Example:
// Input: maxTime = 30, edges = [[0,1,10],[1,2,10],[2,5,10],[0,3,1],[3,4,10],[4,5,15]], passingFees = [5,1,2,20,20,3]
// Output: 11
// Explanation: The path to take is 0 -> 1 -> 2 -> 5, which takes 30 minutes and has $11 worth of passing fees.
//
// Constraints:
// 1 <= maxTime <= 1000
// 	n == passingFees.length
// 	2 <= n <= 1000
// 	n - 1 <= edges.length <= 1000
// 	0 <= xi, yi <= n - 1
// 	1 <= timei <= 1000
// 	1 <= passingFees[j] <= 1000 
// 	The graph may contain multiple edges between two nodes.
// 	The graph does not contain self loops.
//
// Helpful references (internal KB):
// - Bellman-Ford Algorithm (graph, array, bellman-ford, dp-1d)
//   • When to use: Finds single-source shortest paths in a weighted directed graph, especially when negative edge weights are present. It can also detect negative cycles reachable from the source.
//   • Idea: Bellman-Ford iteratively relaxes all edges n-1 times to find single-source shortest paths in a weighted directed graph. It runs in O(VE) time and can detect negative cycles.
//   • Invariants: After k phases, dist[u] holds the shortest path length from source to u using at most k edges.; For any edge (u, v) with weight w, dist[v] <= dist[u] + w if dist[u] is finite and v is reachable.
//   • Tips: Initialize source distance to 0 and all other distances to infinity.; Perform exactly n-1 full passes, relaxing all edges in each pass.
//   • Pitfalls: Incorrectly handling unreachable vertices (distances remaining infinity).; Not detecting negative cycles when they exist, leading to incorrect path lengths.
// - Minimum spanning tree - Prim's algorithm (graph, matrix, array, mst-prim, greedy)
//   • When to use: When you need to find a minimum spanning tree in a connected, weighted graph, especially efficient for dense graphs or when starting from an arbitrary vertex.
//   • Idea: Prim's algorithm is a greedy algorithm that constructs a Minimum Spanning Tree (MST) by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside it. It typically runs in O(E log V) with a priority queue or O(V^2) with an adjacency matrix.
//   • Invariants: The set of edges chosen so far forms a tree (no cycles) and connects a subset of vertices.; At each step, the chosen edge is the minimum weight edge connecting a vertex in the current MST to a vertex outside it.
//   • Tips: Initialize distances (or minimum edge weights) for all vertices not in the MST to infinity.; Use a priority queue to efficiently retrieve the minimum weight edge connecting to the current MST.
//   • Pitfalls: Failing to correctly update edge weights to neighbors when a new vertex is added to the MST.; Not handling disconnected graphs, which will result in only an MST for the starting component.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minCost(int maxTime, int[][] edges, int[] passingFees) {
        int n = passingFees.length;
        int[][] graph = new int[n][n];
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], time = edge[2];
            graph[u][v] = time;
            graph[v][u] = time;
        }

        int[] dp = new int[n];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = passingFees[0];

        for (int t = 0; t < maxTime; t++) {
            int[] nextDp = Arrays.copyOf(dp, n);
            for (int u = 0; u < n; u++) {
                if (dp[u] == Integer.MAX_VALUE) continue;
                for (int v = 0; v < n; v++) {
                    if (graph[u][v] > 0 && t + graph[u][v] <= maxTime) {
                        nextDp[v] = Math.min(nextDp[v], dp[u] + passingFees[v]);
                    }
                }
            }
            dp = nextDp;
        }

        return dp[n - 1] == Integer.MAX_VALUE ? -1 : dp[n - 1];         
    }
}
