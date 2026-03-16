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

/**
 * @param {number} n
 * @param {number[]} nums
 * @param {number} maxDiff
 * @param {number[][]} queries
 * @return {number[]}
 */
var pathExistenceQueries = function(n, nums, maxDiff, queries) {
    const adj = Array.from({ length: n }, () => []);
    const valueToIndices = new Map();
    for (let i = 0; i < n; i++) {
        if (!valueToIndices.has(nums[i])) {
            valueToIndices.set(nums[i], []);
        }
        valueToIndices.get(nums[i]).push(i);
    }
    for (let i = 0; i < n; i++) {
        for (let diff = -maxDiff; diff <= maxDiff; diff++) {
            const neighborValue = nums[i] + diff;
            if (valueToIndices.has(neighborValue)) {
                for (const neighborIndex of valueToIndices.get(neighborValue)) {
                    if (neighborIndex !== i) {
                        adj[i].push(neighborIndex);
                    }
                }
            }
        }
    }
    const results = [];
    for (const [start, end] of queries) {
        const queue = [start];
        const visited = Array(n).fill(false);
        visited[start] = true;
        let distance = 0;
        let found = false;
        while (queue.length > 0) {
            const size = queue.length;
            for (let i = 0; i < size; i++) {
                const node = queue.shift();
                if (node === end) {
                    results.push(distance);
                    found = true;
                    break;
                }
                for (const neighbor of adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        queue.push(neighbor);
                    }
                }
            }
            if (found) break;
            distance++;
        }
        if (!found) {
            results.push(-1);
        }
    }
    return results;
};
