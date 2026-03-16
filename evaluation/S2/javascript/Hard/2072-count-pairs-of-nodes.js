// Source: https://leetcode.com/problems/count-pairs-of-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph defined by an integer n, the number of nodes, and a 2D integer array edges, the edges in the graph, where edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi. You are also given an integer array queries.
//
// Let incident(a, b) be defined as the number of edges that are connected to either node a or b.
//
// The answer to the jth query is the number of pairs of nodes (a, b) that satisfy both of the following conditions:
//
//
// 	a < b
// 	incident(a, b) > queries[j]
//
//
// Return an array answers such that answers.length == queries.length and answers[j] is the answer of the jth query.
//
// Note that there can be multiple edges between the same two nodes.
//
// Example:
// Input: n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
// Output: [6,5]
// Explanation: The calculations for incident(a, b) are shown in the table above.
// The answers for each of the queries are as follows:
// - answers[0] = 6. All the pairs have an incident(a, b) value greater than 2.
// - answers[1] = 5. All the pairs except (3, 4) have an incident(a, b) value greater than 3.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	1 <= edges.length <= 105
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= queries.length <= 20
// 	0 <= queries[j] < edges.length
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} queries
 * @return {number[]}
 */
var countPairs = function(n, edges, queries) {
    const degree = new Array(n + 1).fill(0);
    const edgeCountMap = new Map();
    
    for (const [u, v] of edges) {
        degree[u]++;
        degree[v]++;
        const key = u < v ? `${u},${v}` : `${v},${u}`;
        edgeCountMap.set(key, (edgeCountMap.get(key) || 0) + 1);
    }
    
    const sortedDegrees = degree.slice(1).sort((a, b) => a - b);
    const results = [];
    
    for (const query of queries) {
        let count = 0;
        let left = 0;
        let right = n - 2; // since sortedDegrees is 0-indexed and excludes degree[0]
        
        while (left < right) {
            if (sortedDegrees[left] + sortedDegrees[right] > query) {
                count += right - left;
                right--;
            } else {
                left++;
            }
        }
        
        for (const [key, edgeCount] of edgeCountMap.entries()) {
            const [u, v] = key.split(',').map(Number);
            if (degree[u] + degree[v] > query && degree[u] + degree[v] - edgeCount <= query) {
                count--;
            }
        }
        
        results.push(count);
    }
    
    return results;
};
