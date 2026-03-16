// Source: https://leetcode.com/problems/shortest-cycle-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1. The edges in the graph are represented by a given 2D integer array edges, where edges[i] = [ui, vi] denotes an edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.
//
// Return the length of the shortest cycle in the graph. If no cycle exists, return -1.
//
// A cycle is a path that starts and ends at the same node, and each edge in the path is used only once.
//
// Example:
// Input: n = 7, edges = [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]
// Output: 3
// Explanation: The cycle with the smallest length is : 0 -> 1 -> 2 -> 0
//
// Constraints:
// 2 <= n <= 1000
// 	1 <= edges.length <= 1000
// 	edges[i].length == 2
// 	0 <= ui, vi < n
// 	ui != vi
// 	There are no repeated edges.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var findShortestCycle = function(n, edges) {
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    let shortestCycle = Infinity;
    for (let start = 0; start < n; start++) {
        const queue = [[start, -1, 0]];
        const visited = new Array(n).fill(false);
        visited[start] = true;
        while (queue.length > 0) {
            const [node, parent, distance] = queue.shift();
            for (const neighbor of graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push([neighbor, node, distance + 1]);
                } else if (neighbor !== parent) {
                    shortestCycle = Math.min(shortestCycle, distance + 1);
                }
            }
        }
    }
    return shortestCycle === Infinity ? -1 : shortestCycle;
};
