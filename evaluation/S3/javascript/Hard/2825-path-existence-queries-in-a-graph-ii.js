// Source: https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
//
// You are also given an integer array nums of length n and an integer maxDiff.
//
// An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
//
// You are also given a 2D integer array queries. For each queries[i] = [ui, vi], find the minimum distance between nodes ui and vi. If no path exists between the two nodes, return -1 for that query.
//
// Return an array answer, where answer[i] is the result of the ith query.
//
// Note: The edges between the nodes are unweighted.
//
// Example:
// Input: n = 5, nums = [1,8,3,4,2], maxDiff = 3, queries = [[0,3],[2,4]]
//
// Output: [1,1]
//
// Explanation:
//
// The resulting graph is:
//
//
//
//
// 	
// 		
// 			Query
// 			Shortest Path
// 			Minimum Distance
// 		
// 		
// 			[0, 3]
// 			0 → 3
// 			1
// 		
// 		
// 			[2, 4]
// 			2 → 4
// 			1
// 		
// 	
//
//
// Thus, the output is [1, 1].
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
// 	0 <= maxDiff <= 105
// 	1 <= queries.length <= 105
// 	queries[i] == [ui, vi]
// 	0 <= ui, vi < n
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Undirected Graphs (graph, matrix, simulation)
//   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
//   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
//   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
//   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
//   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[]} nums
 * @param {number} maxDiff
 * @param {number[][]} queries
 * @return {number[]}
 */
var pathExistenceQueries = function(n, nums, maxDiff, queries) {
    const graph = new Array(n).fill(0).map(() => []);
    
    // Build the graph based on the given conditions
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            if (Math.abs(nums[i] - nums[j]) <= maxDiff) {
                graph[i].push(j);
                graph[j].push(i);
            }
        }
    }
            
    // Process queries using DFS
    const results = [];
    for (let [u, v] of queries) {
        if (u === v) {
            results.push(1);
        } else {
            const visited = new Array(n).fill(false);
            const stack = [u];
            visited[u] = true;
            let found = false;
            
            while (stack.length > 0) {
                const current = stack.pop();
                if (current === v) {
                    found = true;
                    break;
                }
                for (let neighbor of graph[current]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        stack.push(neighbor);
                    }
                }
            }
            results.push(found ? 1 : 0);
        }
    }
    return results;
};