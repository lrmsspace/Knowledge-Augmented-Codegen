// Source: https://leetcode.com/problems/largest-color-value-in-a-directed-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is a directed graph of n colored nodes and m edges. The nodes are numbered from 0 to n - 1.
//
// You are given a string colors where colors[i] is a lowercase English letter representing the color of the ith node in this graph (0-indexed). You are also given a 2D array edges where edges[j] = [aj, bj] indicates that there is a directed edge from node aj to node bj.
//
// A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... -> xk such that there is a directed edge from xi to xi+1 for every 1 <= i < k. The color value of the path is the number of nodes that are colored the most frequently occurring color along that path.
//
// Return the largest color value of any valid path in the given graph, or -1 if the graph contains a cycle.
//
// Example:
// Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
// Output: 3
// Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored "a" (red in the above image).
//
// Constraints:
// n == colors.length
// 	m == edges.length
// 	1 <= n <= 105
// 	0 <= m <= 105
// 	colors consists of lowercase English letters.
// 	0 <= aj, bj < n
//

/**
 * @param {string} colors
 * @param {number[][]} edges
 * @return {number}
 */
var largestPathValue = function(colors, edges) {
    const graph = Array.from({ length: colors.length }, () => []);
    const inDegree = new Array(colors.length).fill(0);
    for (const [u, v] of edges) {
        graph[u].push(v);
        inDegree[v]++;
    }
    const queue = [];
    for (let i = 0; i < colors.length; i++) {
        if (inDegree[i] === 0) {
            queue.push(i);
        }
    }
    const colorCount = Array.from({ length: colors.length }, () => new Array(26).fill(0));
    let visited = 0;
    let maxColorValue = 0;
    while (queue.length > 0) {
        const node = queue.shift();
        visited++;
        const colorIndex = colors.charCodeAt(node) - 97;
        colorCount[node][colorIndex]++;
        maxColorValue = Math.max(maxColorValue, colorCount[node][colorIndex]);
        for (const neighbor of graph[node]) {
            for (let i = 0; i < 26; i++) {
                colorCount[neighbor][i] = Math.max(colorCount[neighbor][i], colorCount[node][i]);
            }
            inDegree[neighbor]--;
            if (inDegree[neighbor] === 0) {
                queue.push(neighbor);
            }
        }
    }
    return visited === colors.length ? maxColorValue : -1;
};
