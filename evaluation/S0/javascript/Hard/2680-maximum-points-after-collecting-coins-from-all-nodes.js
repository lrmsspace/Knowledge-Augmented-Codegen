// Source: https://leetcode.com/problems/maximum-points-after-collecting-coins-from-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree rooted at node 0 with n nodes labeled from 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given a 0-indexed array coins of size n where coins[i] indicates the number of coins in the vertex i, and an integer k.
//
// Starting from the root, you have to collect all the coins such that the coins at a node can only be collected if the coins of its ancestors have been already collected.
//
// Coins at nodei can be collected in one of the following ways:
//
//
// 	Collect all the coins, but you will get coins[i] - k points. If coins[i] - k is negative then you will lose abs(coins[i] - k) points.
// 	Collect all the coins, but you will get floor(coins[i] / 2) points. If this way is used, then for all the nodej present in the subtree of nodei, coins[j] will get reduced to floor(coins[j] / 2).
//
//
// Return the maximum points you can get after collecting the coins from all the tree nodes.
//
// Example:
// Input: edges = [[0,1],[1,2],[2,3]], coins = [10,10,3,3], k = 5
// Output: 11                        
// Explanation: 
// Collect all the coins from node 0 using the first way. Total points = 10 - 5 = 5.
// Collect all the coins from node 1 using the first way. Total points = 5 + (10 - 5) = 10.
// Collect all the coins from node 2 using the second way so coins left at node 3 will be floor(3 / 2) = 1. Total points = 10 + floor(3 / 2) = 11.
// Collect all the coins from node 3 using the second way. Total points = 11 + floor(1 / 2) = 11.
// It can be shown that the maximum points we can get after collecting coins from all the nodes is 11.
//
// Constraints:
// n == coins.length
// 	2 <= n <= 105
// 	0 <= coins[i] <= 104
// 	edges.length == n - 1
// 	0 <= edges[i][0], edges[i][1] < n
// 	0 <= k <= 104
//

/**
 * @param {number[][]} edges
 * @param {number[]} coins
 * @param {number} k
 * @return {number}
 */
var maximumPoints = function(edges, coins, k) {
    const n = coins.length;
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    let points = 0;
    const visited = Array(n).fill(false);
    const dfs = (node) => {
        visited[node] = true;
        let pointsIfFirstWay = coins[node] - k;
        let pointsIfSecondWay = Math.floor(coins[node] / 2);
        for (const neighbor of graph[node]) {
            if (!visited[neighbor]) {
                const childPoints = dfs(neighbor);
                pointsIfFirstWay += childPoints;
                pointsIfSecondWay += Math.floor(childPoints / 2);
            }
        }
        points += Math.max(pointsIfFirstWay, pointsIfSecondWay);
        return pointsIfFirstWay > pointsIfSecondWay ? coins[node] : Math.floor(coins[node] / 2);
    }
    dfs(0);
    return points;  
};
