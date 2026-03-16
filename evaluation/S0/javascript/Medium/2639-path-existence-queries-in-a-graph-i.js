// Source: https://leetcode.com/problems/path-existence-queries-in-a-graph-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
//
// You are also given an integer array nums of length n sorted in non-decreasing order, and an integer maxDiff.
//
// An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
//
// You are also given a 2D integer array queries. For each queries[i] = [ui, vi], determine whether there exists a path between nodes ui and vi.
//
// Return a boolean array answer, where answer[i] is true if there exists a path between ui and vi in the ith query and false otherwise.
//
// Example:
// Input: n = 2, nums = [1,3], maxDiff = 1, queries = [[0,0],[0,1]]
//
// Output: [true,false]
//
// Explanation:
//
//
// 	Query [0,0]: Node 0 has a trivial path to itself.
// 	Query [0,1]: There is no edge between Node 0 and Node 1 because |nums[0] - nums[1]| = |1 - 3| = 2, which is greater than maxDiff.
// 	Thus, the final answer after processing all the queries is [true, false].
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
// 	nums is sorted in non-decreasing order.
// 	0 <= maxDiff <= 105
// 	1 <= queries.length <= 105
// 	queries[i] == [ui, vi]
// 	0 <= ui, vi < n
//

/**
 * @param {number} n
 * @param {number[]} nums
 * @param {number} maxDiff
 * @param {number[][]} queries
 * @return {boolean[]}
 */
var pathExistenceQueries = function(n, nums, maxDiff, queries) {
    const parent = Array(n).fill(0).map((_, i) => i);
    const rank = Array(n).fill(1);

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
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    for (let i = 0; i < n - 1; i++) {
        if (Math.abs(nums[i] - nums[i + 1]) <= maxDiff) {
            union(i, i + 1);
        }
    }

    const result = [];
    for (const [u, v] of queries) {
        result.push(find(u) === find(v));
    }
    return result;
};