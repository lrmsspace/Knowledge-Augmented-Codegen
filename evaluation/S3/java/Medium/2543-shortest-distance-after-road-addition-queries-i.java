// Source: https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n and a 2D integer array queries.
//
// There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.
//
// queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.
//
// Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.
//
// Example:
// Input: n = 5, queries = [[2,4],[0,2],[0,4]]
//
// Output: [3,2,1]
//
// Explanation: 
//
//
//
// After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.
//
//
//
// After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.
//
//
//
// After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.
//
// Constraints:
// 3 <= n <= 500
// 	1 <= queries.length <= 500
// 	queries[i].length == 2
// 	0 <= queries[i][0] < queries[i][1] < n
// 	1 < queries[i][1] - queries[i][0]
// 	There are no repeated roads among the queries.
//
// Helpful references (internal KB):
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] shortestDistanceAfterQueries(int n, int[][] queries) {
        int[] answer = new int[queries.length];
        int shortestPath = n - 1; // Initial shortest path from city 0 to city n-1

        for (int i = 0; i < queries.length; i++) {
            int u = queries[i][0];
            int v = queries[i][1];

            // If the new road creates a shorter path from 0 to n-1
            if (u == 0 && v == n - 1) {
                shortestPath = 1; // Direct road from 0 to n-1
            } else if (u == 0) {
                shortestPath = Math.min(shortestPath, v); // Road from 0 to v
            } else if (v == n - 1) {
                shortestPath = Math.min(shortestPath, n - 1 - u); // Road from u to n-1
            }

            answer[i] = shortestPath;
        }

        return answer;          
    }
}
