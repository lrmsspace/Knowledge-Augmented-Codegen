// Source: https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n and an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi] indicates an edge from node ui to vi .
//
// Each node i has an associated cost given by cost[i], representing the cost to traverse that node.
//
// The score of a path is defined as the sum of the costs of all nodes along the path.
//
// Your goal is to make the scores of all root-to-leaf paths equal by increasing the cost of any number of nodes by any non-negative amount.
//
// Return the minimum number of nodes whose cost must be increased to make all root-to-leaf path scores equal.
//
// Example:
// Input: n = 3, edges = [[0,1],[0,2]], cost = [2,1,3]
//
// Output: 1
//
// Explanation:
//
//
//
// There are two root-to-leaf paths:
//
//
// 	Path 0 → 1 has a score of 2 + 1 = 3.
// 	Path 0 → 2 has a score of 2 + 3 = 5.
//
//
// To make all root-to-leaf path scores equal to 5, increase the cost of node 1 by 2.
// Only one node is increased, so the output is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	0 <= ui, vi < n
// 	cost.length == n
// 	1 <= cost[i] <= 109
// 	The input is generated such that edges represents a valid tree.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} cost
 * @return {number}
 */
var minIncrease = function(n, edges, cost) {
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    let maxPathCost = 0;
    const dfs = (node, parent, currentCost) => {
        currentCost += cost[node];
        if (graph[node].length === 1 && node !== 0) {
            maxPathCost = Math.max(maxPathCost, currentCost);
        }                   
        for (const neighbor of graph[node]) {   
            if (neighbor !== parent) {
                dfs(neighbor, node, currentCost);
            }
        }
    }
    dfs(0, -1, 0);
    let increments = 0;
    const dfsCount = (node, parent, currentCost) => {
        currentCost += cost[node];
        if (graph[node].length === 1 && node !== 0) {
            increments += maxPathCost - currentCost;
        }
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                dfsCount(neighbor, node, currentCost);
            }
        }
    }
    dfsCount(0, -1, 0);
    return increments;  
};
