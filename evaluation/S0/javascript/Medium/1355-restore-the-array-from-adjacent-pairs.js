// Source: https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/   |   Difficulty: Medium
//
// Problem Description:
// There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.
//
// You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.
//
// It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.
//
// Return the original array nums. If there are multiple solutions, return any of them.
//
// Example:
// Input: adjacentPairs = [[2,1],[3,4],[3,2]]
// Output: [1,2,3,4]
// Explanation: This array has all its adjacent pairs in adjacentPairs.
// Notice that adjacentPairs[i] may not be in left-to-right order.
//
// Constraints:
// nums.length == n
// 	adjacentPairs.length == n - 1
// 	adjacentPairs[i].length == 2
// 	2 <= n <= 105
// 	-105 <= nums[i], ui, vi <= 105
// 	There exists some nums that has adjacentPairs as its pairs.
//

/**
 * @param {number[][]} adjacentPairs
 * @return {number[]}
 */
var restoreArray = function(adjacentPairs) {
    const graph = new Map();
    for (const [u, v] of adjacentPairs) {
        if (!graph.has(u)) graph.set(u, []);
        if (!graph.has(v)) graph.set(v, []);
        graph.get(u).push(v);
        graph.get(v).push(u);
    }
    let start;
    for (const [node, neighbors] of graph.entries()) {
        if (neighbors.length === 1) {
            start = node;
            break;
        }
    }
    const result = [];
    const visited = new Set();
    let current = start;
    let prev = null;
    while (current !== null) {
        result.push(current);
        visited.add(current);
        const neighbors = graph.get(current);
        let next = null;
        for (const neighbor of neighbors) {
            if (neighbor !== prev) {
                next = neighbor;
                break;
            }
        }
        prev = current;
        current = next;
    }
    return result;
};