// Source: https://leetcode.com/problems/longest-special-path-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0, with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
//
// A special path is defined as a downward path from an ancestor node to a descendant node in which all node values are distinct, except for at most one value that may appear twice.
//
// Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
//
// Example:
// Input: edges = [[0,1,1],[1,2,3],[1,3,1],[2,4,6],[4,7,2],[3,5,2],[3,6,5],[6,8,3]], nums = [1,1,0,3,1,2,1,1,0]
//
// Output: [9,3]
//
// Explanation:
//
// In the image below, nodes are colored by their corresponding values in nums.
//
//
//
// The longest special paths are 1 -> 2 -> 4 and 1 -> 3 -> 6 -> 8, both having a length of 9. The minimum number of nodes across all longest special paths is 3.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= lengthi <= 103
// 	nums.length == n
// 	0 <= nums[i] <= 5 * 104
// 	The input is generated such that edges represents a valid tree.
//

/**
 * @param {number[][]} edges
 * @param {number[]} nums
 * @return {number[]}
 */
var longestSpecialPath = function(edges, nums) {
    const n = nums.length;
    const tree = Array.from({ length: n }, () => []);
    for (const [u, v, length] of edges) {
        tree[u].push([v, length]);
        tree[v].push([u, length]);
    }
    let maxLength = 0;
    let minNodes = Infinity;
    const dfs = (node, parent, seen, length, nodes) => {
        if (length > maxLength) {
            maxLength = length;
            minNodes = nodes;
        } else if (length === maxLength) {
            minNodes = Math.min(minNodes, nodes);
        }
        for (const [child, edgeLength] of tree[node]) {
            if (child === parent) continue;
            const count = seen.get(nums[child]) || 0;
            if (count === 0) {
                seen.set(nums[child], 1);
                dfs(child, node, seen, length + edgeLength, nodes + 1);
                seen.set(nums[child], 0);
            }
            else if (count === 1) {
                seen.set(nums[child], 2);
                dfs(child, node, seen, length + edgeLength, nodes + 1);
                seen.set(nums[child], 1);
            }
        }
    }
    const seen = new Map();
    seen.set(nums[0], 1);
    dfs(0, -1, seen, 0, 1);
    return [maxLength, minNodes];
};
