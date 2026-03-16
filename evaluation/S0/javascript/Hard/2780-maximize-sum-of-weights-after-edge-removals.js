// Source: https://leetcode.com/problems/maximize-sum-of-weights-after-edge-removals/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.
//
// Your task is to remove zero or more edges such that:
//
//
// 	Each node has an edge with at most k other nodes, where k is given.
// 	The sum of the weights of the remaining edges is maximized.
//
//
// Return the maximum possible sum of weights for the remaining edges after making the necessary removals.
//
// Example:
// Input: edges = [[0,1,4],[0,2,2],[2,3,12],[2,4,6]], k = 2
//
// Output: 22
//
// Explanation:
//
//
//
//
// 	Node 2 has edges with 3 other nodes. We remove the edge [0, 2, 2], ensuring that no node has edges with more than k = 2 nodes.
// 	The sum of weights is 22, and we can't achieve a greater sum. Thus, the answer is 22.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= k <= n - 1
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= edges[i][0] <= n - 1
// 	0 <= edges[i][1] <= n - 1
// 	1 <= edges[i][2] <= 106
// 	The input is generated such that edges form a valid tree.
//

/**
 * @param {number[][]} edges
 * @param {number} k
 * @return {number}
 */
var maximizeSumOfWeights = function(edges, k) {
    const n = edges.length + 1;
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v, w] of edges) {
        graph[u].push([v, w]);
        graph[v].push([u, w]);
    }
    const dp = Array.from({ length: n }, () => Array(2).fill(0));
    const visited = new Array(n).fill(false);
    const dfs = (node) => {
        visited[node] = true;
        const diffs = [];
        let total = 0;
        for (const [neighbor, weight] of graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
                total += dp[neighbor][0];
                diffs.push(dp[neighbor][1] + weight - dp[neighbor][0]);
            }
        }
        diffs.sort((a, b) => b - a);
        dp[node][0] = total;
        for (let i = 0; i < Math.min(k, diffs.length); i++) {
            if (diffs[i] > 0) {
                dp[node][0] += diffs[i];
            }
        }
        dp[node][1] = total;            
        for (let i = 0; i < Math.min(k - 1, diffs.length); i++) {
            if (diffs[i] > 0) {
                dp[node][1] += diffs[i];
            }
        }
    }
    dfs(0);
    return dp[0][0];
};
