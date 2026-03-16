// Source: https://leetcode.com/problems/shortest-path-with-alternating-colors/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
//
// You are given two arrays redEdges and blueEdges where:
//
//
// 	redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
// 	blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.
//
//
// Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
//
// Example:
// Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
// Output: [0,1,-1]
//
// Constraints:
// 1 <= n <= 100
// 	0 <= redEdges.length, blueEdges.length <= 400
// 	redEdges[i].length == blueEdges[j].length == 2
// 	0 <= ai, bi, uj, vj < n
//

/**
 * @param {number} n
 * @param {number[][]} redEdges
 * @param {number[][]} blueEdges
 * @return {number[]}
 */
var shortestAlternatingPaths = function(n, redEdges, blueEdges) {
    const graph = Array.from({ length: n }, () => ({ red: [], blue: [] }));
    for (const [from, to] of redEdges) {
        graph[from].red.push(to);
    }
    for (const [from, to] of blueEdges) {
        graph[from].blue.push(to);
    }
    const result = Array(n).fill(-1);
    const queue = [];
    const visited = Array.from({ length: n }, () => ({ red: false, blue: false }));
    queue.push([0, 0, null]); // [node, distance, color]
    visited[0].red = true;
    visited[0].blue = true;
    while (queue.length > 0) {
        const [node, distance, color] = queue.shift();
        if (result[node] === -1) {
            result[node] = distance;
        }
        const nextColor = color === 'red' ? 'blue' : 'red';
        for (const neighbor of graph[node][nextColor]) {
            if (!visited[neighbor][nextColor]) {
                visited[neighbor][nextColor] = true;
                queue.push([neighbor, distance + 1, nextColor]);
            }
        }
    }
    return result;
        
};
