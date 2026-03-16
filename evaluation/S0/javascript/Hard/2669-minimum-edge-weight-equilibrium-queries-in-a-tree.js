// Source: https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.
//
// You are also given a 2D integer array queries of length m, where queries[i] = [ai, bi]. For each query, find the minimum number of operations required to make the weight of every edge on the path from ai to bi equal. In one operation, you can choose any edge of the tree and change its weight to any value.
//
// Note that:
//
//
// 	Queries are independent of each other, meaning that the tree returns to its initial state on each new query.
// 	The path from ai to bi is a sequence of distinct nodes starting with node ai and ending with node bi such that every two adjacent nodes in the sequence share an edge in the tree.
//
//
// Return an array answer of length m where answer[i] is the answer to the ith query.
//
// Example:
// Input: n = 7, edges = [[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]], queries = [[0,3],[3,6],[2,6],[0,6]]
// Output: [0,0,1,3]
// Explanation: In the first query, all the edges in the path from 0 to 3 have a weight of 1. Hence, the answer is 0.
// In the second query, all the edges in the path from 3 to 6 have a weight of 2. Hence, the answer is 0.
// In the third query, we change the weight of edge [2,3] to 2. After this operation, all the edges in the path from 2 to 6 have a weight of 2. Hence, the answer is 1.
// In the fourth query, we change the weights of edges [0,1], [1,2] and [2,3] to 2. After these operations, all the edges in the path from 0 to 6 have a weight of 2. Hence, the answer is 3.
// For each queries[i], it can be shown that answer[i] is the minimum number of operations needed to equalize all the edge weights in the path from ai to bi.
//
// Constraints:
// 1 <= n <= 104
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= wi <= 26
// 	The input is generated such that edges represents a valid tree.
// 	1 <= queries.length == m <= 2 * 104
// 	queries[i].length == 2
// 	0 <= ai, bi < n
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[][]} queries
 * @return {number[]}
 */
var minOperationsQueries = function(n, edges, queries) {
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v, w] of edges) {
        graph[u].push([v, w]);
        graph[v].push([u, w]);
    }
    const parent = new Array(n).fill(-1);
    const depth = new Array(n).fill(0);
    const weight = new Array(n).fill(0);
    const dfs = (node, par) => {
        for (const [neighbor, w] of graph[node]) {
            if (neighbor !== par) {
                parent[neighbor] = node;
                depth[neighbor] = depth[node] + 1;
                weight[neighbor] = w;
                dfs(neighbor, node);
            }
        }   
    };
    dfs(0, -1);
    const lca = (u, v) => {
        if (depth[u] < depth[v]) {
            [u, v] = [v, u];
        }
        while (depth[u] > depth[v]) {
            u = parent[u];
        }
        while (u !== v) {
            u = parent[u];
            v = parent[v];
        }
        return u;
    }
    const answer = [];
    for (const [a, b] of queries) {
        const ancestor = lca(a, b);
        const freq = new Array(27).fill(0);
        let count = 0;
        let current = a;
        while (current !== ancestor) {
            freq[weight[current]]++;
            current = parent[current];
        }   
        current = b;
        while (current !== ancestor) {
            freq[weight[current]]++;
            current = parent[current];
        }
        for (const f of freq) {
            count = Math.max(count, f);
        }
        const totalEdges = depth[a] + depth[b] - 2 * depth[ancestor];
        answer.push(totalEdges - count);
    }
    return answer;  
};
