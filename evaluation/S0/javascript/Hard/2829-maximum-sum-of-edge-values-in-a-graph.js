// Source: https://leetcode.com/problems/maximum-sum-of-edge-values-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected connected graph of n nodes, numbered from 0 to n - 1. Each node is connected to at most 2 other nodes.
//
// The graph consists of m edges, represented by a 2D array edges, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi.
//
// You have to assign a unique value from 1 to n to each node. The value of an edge will be the product of the values assigned to the two nodes it connects.
//
// Your score is the sum of the values of all edges in the graph.
//
// Return the maximum score you can achieve.
//
// Example:
// Input: n = 4, edges = [[0,1],[1,2],[2,3]]
//
// Output: 23
//
// Explanation:
//
// The diagram above illustrates an optimal assignment of values to nodes. The sum of the values of the edges is: (1 * 3) + (3 * 4) + (4 * 2) = 23.
//
// Constraints:
// 1 <= n <= 5 * 104
// 	m == edges.length
// 	1 <= m <= n
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	There are no repeated edges.
// 	The graph is connected.
// 	Each node is connected to at most 2 other nodes.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var maxScore = function(n, edges) {
    const degree = new Array(n).fill(0);
    for (const [u, v] of edges) {
        degree[u]++;
        degree[v]++;
    }
    const values = new Array(n);
    for (let i = 0; i < n; i++) {
        values[i] = i + 1;
    }
    values.sort((a, b) => b - a);
    const assigned = new Array(n).fill(false);
    let score = 0;
    for (const [u, v] of edges) {
        if (!assigned[u] && !assigned[v]) {
            if (degree[u] > degree[v]) {
                assigned[u] = true;
                score += values[u - 1] * values[v - 1];
            } else {
                assigned[v] = true;
                score += values[u - 1] * values[v - 1];
            }
        } else if (!assigned[u]) {
            assigned[u] = true;
            score += values[u - 1] * values[v - 1];
        } else if (!assigned[v]) {
            assigned[v] = true;
            score += values[u - 1] * values[v - 1];
        } else {
            score += values[u - 1] * values[v - 1];
        }
    }
    return score;
};
