// Source: https://leetcode.com/problems/shortest-path-visiting-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.
//
// Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
//
// Example:
// Input: graph = [[1,2,3],[0],[0],[0]]
// Output: 4
// Explanation: One possible path is [1,0,2,0,3]
//
// Constraints:
// n == graph.length
// 	1 <= n <= 12
// 	0 <= graph[i].length < n
// 	graph[i] does not contain i.
// 	If graph[a] contains b, then graph[b] contains a.
// 	The input graph is always connected.
//

/**
 * @param {number[][]} graph
 * @return {number}
 */
var shortestPathLength = function(graph) {
    const n = graph.length;
    const queue = [];
    const visited = new Set();

    for (let i = 0; i < n; i++) {
        const state = (1 << i) | (i << 16);
        queue.push(state);
        visited.add(state);
    }
    let steps = 0;

    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const state = queue.shift();
            const mask = state & 0xFFFF;
            const node = state >> 16;
            if (mask === (1 << n) - 1) {
                return steps;
            }
            for (const neighbor of graph[node]) {
                const nextMask = mask | (1 << neighbor);
                const nextState = nextMask | (neighbor << 16);
                if (!visited.has(nextState)) {
                    visited.add(nextState);
                    queue.push(nextState);
                }
            }
        }
        steps++;
    }
    return -1; // This line should never be reached since the graph is connected    

}
