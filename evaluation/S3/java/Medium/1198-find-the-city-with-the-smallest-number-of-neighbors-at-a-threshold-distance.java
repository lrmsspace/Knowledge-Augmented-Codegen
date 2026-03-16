// Source: https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/   |   Difficulty: Medium
//
// Problem Description:
// There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.
//
// Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.
//
// Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.
//
// Example:
// Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
// Output: 3
// Explanation: The figure above describes the graph. 
// The neighboring cities at a distanceThreshold = 4 for each city are:
// City 0 -> [City 1, City 2] 
// City 1 -> [City 0, City 2, City 3] 
// City 2 -> [City 0, City 1, City 3] 
// City 3 -> [City 1, City 2] 
// Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.
//
// Constraints:
// 2 <= n <= 100
// 	1 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 3
// 	0 <= fromi < toi < n
// 	1 <= weighti, distanceThreshold <= 10^4
// 	All pairs (fromi, toi) are distinct.
//
// Helpful references (internal KB):
// - Floyd-Warshall Algorithm (number, simulation)
//   • When to use: When you need to find the shortest paths between all possible pairs of vertices in a graph. It is particularly suitable for dense graphs or when negative edge weights are present, as long as no negative cycles are reachable.
//   • Idea: Floyd-Warshall is a dynamic programming algorithm that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path distances, achieving an O(V^3) time complexity.
//   • Invariants: After the k-th iteration, dist[i][j] contains the shortest path from i to j considering only vertices 0 to k-1 as intermediate nodes.; For any pair (i, j), dist[i][j] is always greater than or equal to the true shortest path distance from i to j (or infinity if unreachable).
//   • Tips: Initialize distances: direct edge weights, infinity for no direct edge, zero for self-loops.; The outermost loop must iterate through intermediate vertices (k).
//   • Pitfalls: Incorrect loop order (k not outermost) leads to incorrect results.; Integer overflow with large path sums if not using appropriate data types.
// - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
//   • When to use: Use when you need to find the shortest paths between all pairs of vertices in a weighted graph, especially if it contains negative edge weights but no negative cycles. It is well-suited for dense graphs.
//   • Idea: The Floyd-Warshall algorithm computes all-pairs shortest paths in a weighted graph by iteratively considering all vertices as intermediate nodes. It is a dynamic programming approach with a time complexity of O(V^3).
//   • Invariants: After the k-th outer loop iteration, dist[i][j] holds the shortest path from i to j using only vertices 0 to k-1 as intermediate nodes.; For any i, dist[i][i] is non-positive; if dist[i][i] < 0, a negative cycle exists through i.
//   • Tips: Initialize dist[i][j] with edge weights, 0 for i=j, and infinity otherwise.; After running, check dist[t][t] < 0 for any t to detect negative cycles.
//   • Pitfalls: Floating-point errors accumulate exponentially, making it unsuitable for high-precision float weights.; Standard algorithm does not correctly handle paths involving negative cycles; special detection is required.
// - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
//   • When to use: Use when needing to find the shortest paths between all pairs of vertices in a weighted graph, especially if negative edge weights are present but no negative cycles.
//   • Idea: The Floyd-Warshall algorithm is a dynamic programming approach that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path lengths, achieving an O(N^3) time complexity.
//   • Invariants: After k iterations, d[i][j] stores the shortest path from i to j using only vertices {1, ..., k} as intermediate nodes.; d[i][j] always represents a valid path length or infinity, never an invalid negative value unless a negative cycle is detected.
//   • Tips: Initialize direct edge weights and infinity for non-existent edges.; Set distance from a vertex to itself to zero initially.
//   • Pitfalls: Incorrect loop order (k must be outermost) will yield incorrect results.; Improper handling of 'infinity' values can lead to overflow or incorrect comparisons.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int findTheCity(int n, int[][] edges, int distanceThreshold) {
        int[][] dist = new int[n][n];
        for (int i = 0; i < n; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
            dist[i][i] = 0;
        }
        for (int[] edge : edges) {
            int from = edge[0], to = edge[1], weight = edge[2];
            dist[from][to] = weight;
            dist[to][from] = weight;
        }

        // Floyd-Warshall Algorithm
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != Integer.MAX_VALUE && dist[k][j] != Integer.MAX_VALUE) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        int minNeighbors = Integer.MAX_VALUE;
        int resultCity = -1;

        for (int i = 0; i < n; i++) {
            int neighborsCount = 0;
            for (int j = 0; j < n; j++) {
                if (i != j && dist[i][j] <= distanceThreshold) {
                    neighborsCount++;
                }
            }
            if (neighborsCount < minNeighbors || (neighborsCount == minNeighbors && i > resultCity)) {
                minNeighbors = neighborsCount;
                resultCity = i;
            }
        }

        return resultCity;          
    }
}
