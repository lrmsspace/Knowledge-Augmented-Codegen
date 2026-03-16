// Source: https://leetcode.com/problems/longest-special-path/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1, represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with length lengthi. You are also given an integer array nums, where nums[i] represents the value at node i.
//
// A special path is defined as a downward path from an ancestor node to a descendant node such that all the values of the nodes in that path are unique.
//
// Note that a path may start and end at the same node.
//
// Return an array result of size 2, where result[0] is the length of the longest special path, and result[1] is the minimum number of nodes in all possible longest special paths.
//
// Example:
// Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], nums = [2,1,2,1,3,1]
//
// Output: [6,2]
//
// Explanation:
//
// In the image below, nodes are colored by their corresponding values in nums
//
//
//
// The longest special paths are 2 -> 5 and 0 -> 1 -> 4, both having a length of 6. The minimum number of nodes across all longest special paths is 2.
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
    const visited = new Set();
    function dfs(node, currentLength, currentNodes) {
        visited.add(nums[node]);
        let isLeaf = true;
        for (const [neighbor, length] of tree[node]) {
            if (!visited.has(nums[neighbor])) {
                isLeaf = false;
                dfs(neighbor, currentLength + length, currentNodes + 1);
            }
        }
        if (isLeaf) {
            if (currentLength > maxLength) {
                maxLength = currentLength;
                minNodes = currentNodes;
            } else if (currentLength === maxLength) {
                minNodes = Math.min(minNodes, currentNodes);
            }
        }
        visited.delete(nums[node]);
    }   
    dfs(0, 0, 1);
    return [maxLength, minNodes];
};
