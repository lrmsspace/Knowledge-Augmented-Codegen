// Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted tree with n nodes, numbered from 0 to n - 1. It is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi.​
//
// Additionally, you are given a 2D integer array queries, where queries[j] = [src1j, src2j, destj].
//
// Return an array answer of length equal to queries.length, where answer[j] is the minimum total weight of a subtree such that it is possible to reach destj from both src1j and src2j using edges in this subtree.
//
// A subtree here is any connected subset of nodes and edges of the original tree forming a valid tree.
//
// Example:
// Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], queries = [[2,3,4],[0,2,5]]
//
// Output: [12,11]
//
// Explanation:
//
// The blue edges represent one of the subtrees that yield the optimal answer.
//
//
//
//
// 	
// 	answer[0]: The total weight of the selected subtree that ensures a path from src1 = 2 and src2 = 3 to dest = 4 is 3 + 5 + 4 = 12.
// 	
// 	
// 	answer[1]: The total weight of the selected subtree that ensures a path from src1 = 0 and src2 = 2 to dest = 5 is 2 + 3 + 6 = 11.
//
// Constraints:
// 3 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= wi <= 104
// 	1 <= queries.length <= 105
// 	queries[j].length == 3
// 	0 <= src1j, src2j, destj < n
// 	src1j, src2j, and destj are pairwise distinct.
// 	The input is generated such that edges represents a valid tree.
//

/**
 * @param {number[][]} edges
 * @param {number[][]} queries
 * @return {number[]}
 */
var minimumWeight = function(edges, queries) {
    const n = edges.length + 1;
    const graph = new Array(n).fill(0).map(() => []);
    for (const [u, v, w] of edges) {
        graph[u].push([v, w]);
        graph[v].push([u, w]);
    }
    const LOG = 17;
    const parent = new Array(n).fill(0).map(() => new Array(LOG).fill(-1));
    const depth = new Array(n).fill(0);
    const dist = new Array(n).fill(0);
    const dfs = (u, p) => {
        for (const [v, w] of graph[u]) {
            if (v !== p) {
                parent[v][0] = u;
                depth[v] = depth[u] + 1;
                dist[v] = dist[u] + w;
                dfs(v, u);
            }
        }
    };
    dfs(0, -1);
    for (let j = 1; j < LOG; j++) {
        for (let i = 0; i < n; i++) {
            if (parent[i][j - 1] !== -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    const lca = (u, v) => {
        if (depth[u] < depth[v]) {
            [u, v] = [v, u];
        }
        for (let j = LOG - 1; j >= 0; j--) {
            if (parent[u][j] !== -1 && depth[parent[u][j]] >= depth[v]) {
                u = parent[u][j];
            }
        }
        if (u === v) {
            return u;
        }
        for (let j = LOG - 1; j >= 0; j--) {
            if (parent[u][j] !== -1 && parent[u][j] !== parent[v][j]) {
                u = parent[u][j];
                v = parent[v][j];
            }
        }
        return parent[u][0];
    }
    const results = []; 
    for (const [src1, src2, dest] of queries) {
        const lca1 = lca(src1, dest);
        const lca2 = lca(src2, dest);
        const lca3 = lca(src1, src2);
        const totalDist = dist[src1] + dist[src2] + dist[dest];
        const overlapDist = dist[lca1] + dist[lca2] + dist[lca3];
        results.push(totalDist - overlapDist);
    }
    return results;
};
