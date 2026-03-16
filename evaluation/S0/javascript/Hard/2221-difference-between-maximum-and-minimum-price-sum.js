// Source: https://leetcode.com/problems/difference-between-maximum-and-minimum-price-sum/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected and initially unrooted tree with n nodes indexed from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Each node has an associated price. You are given an integer array price, where price[i] is the price of the ith node.
//
// The price sum of a given path is the sum of the prices of all nodes lying on that path.
//
// The tree can be rooted at any node root of your choice. The incurred cost after choosing root is the difference between the maximum and minimum price sum amongst all paths starting at root.
//
// Return the maximum possible cost amongst all possible root choices.
//
// Example:
// Input: n = 6, edges = [[0,1],[1,2],[1,3],[3,4],[3,5]], price = [9,8,7,6,10,5]
// Output: 24
// Explanation: The diagram above denotes the tree after rooting it at node 2. The first part (colored in red) shows the path with the maximum price sum. The second part (colored in blue) shows the path with the minimum price sum.
// - The first path contains nodes [2,1,3,4]: the prices are [7,8,6,10], and the sum of the prices is 31.
// - The second path contains the node [2] with the price [7].
// The difference between the maximum and minimum price sum is 24. It can be proved that 24 is the maximum cost.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	0 <= ai, bi <= n - 1
// 	edges represents a valid tree.
// 	price.length == n
// 	1 <= price[i] <= 105
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} price
 * @return {number}
 */
var maxOutput = function(n, edges, price) {
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    const subtreeMax = new Array(n).fill(0);
    const dfs = (node, parent) => {
        subtreeMax[node] = price[node];
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                dfs(neighbor, node);
                subtreeMax[node] = Math.max(subtreeMax[node], price[node] + subtreeMax[neighbor]);
            }
        }
    };
    dfs(0, -1);
    let result = 0;
    const dfs2 = (node, parent, maxUp) => {
        const maxDown = subtreeMax[node];
        result = Math.max(result, maxUp + maxDown - price[node]);
        const prefixMax = [];
        const suffixMax = [];
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                prefixMax.push(subtreeMax[neighbor]);
                suffixMax.push(subtreeMax[neighbor]);
            }
        }
        for (let i = 1; i < prefixMax.length; i++) {
            prefixMax[i] = Math.max(prefixMax[i], prefixMax[i - 1]);
        }
        for (let i = suffixMax.length - 2; i >= 0; i--) {
            suffixMax[i] = Math.max(suffixMax[i], suffixMax[i + 1]);
        }
        let idx = 0;
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                const maxSibling = Math.max(idx > 0 ? prefixMax[idx - 1] : 0, idx < suffixMax.length - 1 ? suffixMax[idx + 1] : 0);
                dfs2(neighbor, node, Math.max(maxUp, maxSibling) + price[node]);
                idx++;
            }
        }
    };  
    dfs2(0, -1, 0);
    return result;
};
