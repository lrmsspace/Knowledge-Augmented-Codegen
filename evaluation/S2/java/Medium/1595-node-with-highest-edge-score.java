// Source: https://leetcode.com/problems/node-with-highest-edge-score/   |   Difficulty: Medium
//
// Problem Description:
// You are given a directed graph with n nodes labeled from 0 to n - 1, where each node has exactly one outgoing edge.
//
// The graph is represented by a given 0-indexed integer array edges of length n, where edges[i] indicates that there is a directed edge from node i to node edges[i].
//
// The edge score of a node i is defined as the sum of the labels of all the nodes that have an edge pointing to i.
//
// Return the node with the highest edge score. If multiple nodes have the same edge score, return the node with the smallest index.
//
// Example:
// Input: edges = [1,0,0,0,0,7,7,5]
// Output: 7
// Explanation:
// - The nodes 1, 2, 3 and 4 have an edge pointing to node 0. The edge score of node 0 is 1 + 2 + 3 + 4 = 10.
// - The node 0 has an edge pointing to node 1. The edge score of node 1 is 0.
// - The node 7 has an edge pointing to node 5. The edge score of node 5 is 7.
// - The nodes 5 and 6 have an edge pointing to node 7. The edge score of node 7 is 5 + 6 = 11.
// Node 7 has the highest edge score so return 7.
//
// Constraints:
// n == edges.length
// 	2 <= n <= 105
// 	0 <= edges[i] < n
// 	edges[i] != i
//
// Helpful references (internal KB):
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
//   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
//   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
//   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
//   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
// - Finding a negative cycle in the graph (graph, array, bellman-ford)
//   • When to use: Use when a graph may contain negative edge weights and you need to find the shortest paths from a single source, or specifically to detect and identify negative cycles.
//   • Idea: The Bellman-Ford algorithm computes single-source shortest paths in a weighted graph, even with negative edge weights, and can detect negative cycles. It has a time complexity of O(VE).
//   • Invariants: After k iterations, dist[v] is the shortest path from the source to v using at most k edges.; If no negative cycle is reachable, dist[v] will be the true shortest path distance after V-1 iterations.
//   • Tips: Perform V-1 iterations for shortest path calculation, then one more for cycle detection.; A negative cycle exists if any distance can still be reduced in the V-th iteration.
//   • Pitfalls: Inefficient for graphs with only non-negative weights compared to Dijkstra's.; Does not directly work for undirected graphs with negative edges.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int edgeScore(int[] edges) {
        int n = edges.length;
        long[] scores = new long[n];
        for (int i = 0; i < n; i++) {
            scores[edges[i]] += i;
        }

        int maxNode = 0;
        for (int i = 1; i < n; i++) {
            if (scores[i] > scores[maxNode]) {
                maxNode = i;
            }
        }
        return maxNode;         
    }
}
