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
// - N/A
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
    const edges = [];
    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            if (Math.abs(nums[i] - nums[j]) <= maxDiff) {
                edges.push([i, j]);
            }
        }
    }

    const parent = new Array(n);
    const rank = new Array(n).fill(0);
    for (let i = 0; i < n; i++) {
        parent[i] = i;
    }

    function find(x) {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    function union(x, y) {
        const rootX = find(x);
        const rootY = find(y);
        if (rootX !== rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    for (const [u, v] of edges) {
        union(u, v);
    }

    return queries.map(([u, v]) => find(u) === find(v) ? 1 : -1);
};
