// Source: https://leetcode.com/problems/shortest-path-in-a-weighted-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge from node ui to vi with weight wi.
//
// You are also given a 2D integer array queries of length q, where each queries[i] is either:
//
//
// 	[1, u, v, w'] – Update the weight of the edge between nodes u and v to w', where (u, v) is guaranteed to be an edge present in edges.
// 	[2, x] – Compute the shortest path distance from the root node 1 to node x.
//
//
// Return an integer array answer, where answer[i] is the shortest path distance from node 1 to x for the ith query of [2, x].
//
// Example:
// Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]
//
// Output: [7,4]
//
// Explanation:
//
//
//
//
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 7.
// 	Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 4.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	1 <= ui, vi <= n
// 	1 <= wi <= 104
// 	The input is generated such that edges represents a valid tree.
// 	1 <= queries.length == q <= 105
// 	queries[i].length == 2 or 4
// 	
// 		queries[i] == [1, u, v, w'] or,
// 		queries[i] == [2, x]
// 		1 <= u, v, x <= n
// 		(u, v) is always an edge from edges.
// 		1 <= w' <= 104
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[][]} queries
 * @return {number[]}
 */
var treeQueries = function(n, edges, queries) {
    const adj = Array.from({ length: n + 1 }, () => []);
    const edgeWeights = new Map();
    for (const [u, v, w] of edges) {
        adj[u].push(v);
        adj[v].push(u);
        edgeWeights.set(`${Math.min(u, v)}#${Math.max(u, v)}`, w);
    }
    const parent = Array(n + 1).fill(0);
    const depth = Array(n + 1).fill(0);
    const distFromRoot = Array(n + 1).fill(0);
    const dfs = (node, par) => {
        for (const neighbor of adj[node]) {
            if (neighbor !== par) {
                parent[neighbor] = node;
                depth[neighbor] = depth[node] + 1;
                distFromRoot[neighbor] = distFromRoot[node] + edgeWeights.get(`${Math.min(node, neighbor)}#${Math.max(node, neighbor)}`);
                dfs(neighbor, node);
            }
        }
    };
    dfs(1, -1);
    const results = [];
    for (const query of queries) {
        if (query[0] === 1) {
            const [, u, v, newWeight] = query;
            const key = `${Math.min(u, v)}#${Math.max(u, v)}`;
            const oldWeight = edgeWeights.get(key);
            edgeWeights.set(key, newWeight);
            const diff = newWeight - oldWeight;
            const child = depth[u] > depth[v] ? u : v;
            const stack = [child];
            while (stack.length) {
                const curr = stack.pop();
                distFromRoot[curr] += diff;
                for (const neighbor of adj[curr]) {
                    if (neighbor !== parent[curr]) {
                        stack.push(neighbor);
                    }
                }
            }
        } else {
            const [, x] = query;
            results.push(distFromRoot[x]);
        }
    }
    return results;
};
