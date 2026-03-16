// Source: https://leetcode.com/problems/find-weighted-median-node-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from node ui to vi with weight wi.
//
// The weighted median node is defined as the first node x on the path from ui to vi such that the sum of edge weights from ui to x is greater than or equal to half of the total path weight.
//
// You are given a 2D integer array queries. For each queries[j] = [uj, vj], determine the weighted median node along the path from uj to vj.
//
// Return an array ans, where ans[j] is the node index of the weighted median for queries[j].
//
// Example:
// Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
//
// Output: [0,1]
//
// Explanation:
//
//
//
//
// 	
// 		
// 			Query
// 			Path
// 			Edge
// 			Weights
// 			Total
// 			Path
// 			Weight
// 			Half
// 			Explanation
// 			Answer
// 		
// 	
// 	
// 		
// 			[1, 0]
// 			1 → 0
// 			[7]
// 			7
// 			3.5
// 			Sum from 1 → 0 = 7 >= 3.5, median is node 0.
// 			0
// 		
// 		
// 			[0, 1]
// 			0 → 1
// 			[7]
// 			7
// 			3.5
// 			Sum from 0 → 1 = 7 >= 3.5, median is node 1.
// 			1
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	0 <= ui, vi < n
// 	1 <= wi <= 109
// 	1 <= queries.length <= 105
// 	queries[j] == [uj, vj]
// 	0 <= uj, vj < n
// 	The input is generated such that edges represents a valid tree.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[][]} queries
 * @return {number[]}
 */
var findMedian = function(n, edges, queries) {
    const LOG = 17;
    const graph = new Array(n).fill(0).map(() => []);
    for (const [u, v, w] of edges) {
        graph[u].push([v, w]);
        graph[v].push([u, w]);
    }
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
    const getKthAncestor = (u, k) => {
        for (let j = 0; j < LOG; j++) {
            if ((k & (1 << j)) !== 0) {
                u = parent[u][j];
                if (u === -1) break;
            }
        }
        return u;
    }
    const results = [];
    for (const [u, v] of queries) {
        const lcaNode = lca(u, v);
        const totalDist = dist[u] + dist[v] - 2 * dist[lcaNode];
        const halfDist = totalDist / 2;
        let medianNode;
        if (dist[u] - dist[lcaNode] >= halfDist) {
            let curr = u;
            for (let j = LOG - 1; j >= 0; j--) {
                if (parent[curr][j] !== -1 && dist[u] - dist[parent[curr][j]] < halfDist) {
                    curr = parent[curr][j];
                }
            }
            medianNode = curr;
        }
        else {
            let curr = v;
            const distFromLcaToMedian = halfDist - (dist[u] - dist[lcaNode]);
            for (let j = LOG - 1; j >= 0; j--) {
                if (parent[curr][j] !== -1 && dist[curr] - dist[parent[curr][j]] < distFromLcaToMedian) {
                    curr = parent[curr][j];
                }
            }
            medianNode = curr;
        }
        results.push(medianNode);
    }
    return results;
};
