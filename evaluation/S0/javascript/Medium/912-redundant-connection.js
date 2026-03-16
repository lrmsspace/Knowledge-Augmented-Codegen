// Source: https://leetcode.com/problems/redundant-connection/   |   Difficulty: Medium
//
// Problem Description:
// In this problem, a tree is an undirected graph that is connected and has no cycles.
//
// You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.
//
// Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.
//
// Example:
// Input: edges = [[1,2],[1,3],[2,3]]
// Output: [2,3]
//
// Constraints:
// n == edges.length
// 	3 <= n <= 1000
// 	edges[i].length == 2
// 	1 <= ai < bi <= edges.length
// 	ai != bi
// 	There are no repeated edges.
// 	The given graph is connected.
//

/**
 * @param {number[][]} edges
 * @return {number[]}
 */
var findRedundantConnection = function(edges) {
    const parent = Array(edges.length + 1).fill(0).map((_, index) => index);

    const find = (x) => {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };  
    for (const [u, v] of edges) {
        const rootU = find(u);
        const rootV = find(v);
        if (rootU === rootV) {
            return [u, v];
        }
        parent[rootU] = rootV;
    }
    return [];  
};
