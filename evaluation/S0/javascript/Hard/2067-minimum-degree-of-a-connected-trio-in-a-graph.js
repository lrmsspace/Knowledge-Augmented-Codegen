// Source: https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph. You are given an integer n which is the number of nodes in the graph and an array edges, where each edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi.
//
// A connected trio is a set of three nodes where there is an edge between every pair of them.
//
// The degree of a connected trio is the number of edges where one endpoint is in the trio, and the other is not.
//
// Return the minimum degree of a connected trio in the graph, or -1 if the graph has no connected trios.
//
// Example:
// Input: n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
// Output: 3
// Explanation: There is exactly one trio, which is [1,2,3]. The edges that form its degree are bolded in the figure above.
//
// Constraints:
// 2 <= n <= 400
// 	edges[i].length == 2
// 	1 <= edges.length <= n * (n-1) / 2
// 	1 <= ui, vi <= n
// 	ui != vi
// 	There are no repeated edges.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var minTrioDegree = function(n, edges) {
    const graph = Array.from({ length: n + 1 }, () => new Set());
    for (const [u, v] of edges) {
        graph[u].add(v);
        graph[v].add(u);
    }
    let minDegree = Infinity;
    for (let i = 1; i <= n; i++) {
        for (const j of graph[i]) {
            for (const k of graph[j]) {
                if (k !== i && graph[i].has(k)) {
                    const degree = graph[i].size + graph[j].size + graph[k].size - 6;
                    minDegree = Math.min(minDegree, degree);
                }
            }
        }
    }
    return minDegree === Infinity ? -1 : minDegree;
};
