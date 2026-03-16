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
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Finding bridges in a graph in O(N+M) (graph, array, dfs)
//   • When to use: Use this algorithm when you need to identify edges whose removal would increase the number of connected components in an undirected graph. It's suitable for analyzing network robustness or critical connections.
//   • Idea: This algorithm uses Depth First Search (DFS) to find bridges in an undirected graph by tracking discovery times and the lowest reachable discovery time from a node or its descendants. It operates in linear time, O(N+M), where N is the number of vertices and M is the number of edges.
//   • Invariants: For any node `u` currently in the DFS stack, `tin[u]` is its unique discovery time.; For any node `u` and its child `v` in the DFS tree, `low[v]` represents the earliest discovery time reachable from `v`'s subtree (including `v`) using at most one back-edge.
//   • Tips: Initialize discovery times (tin) and lowest reachable times (low) arrays, along with a visited array.; Pass the parent vertex to the DFS function to avoid treating the parent edge as a back-edge.
//   • Pitfalls: Forgetting to pass the parent node or incorrectly handling the parent edge, leading to false bridge detections.; Failing to initialize `low` values correctly, especially for leaf nodes or isolated components.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

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
    
    const dfs = (node, parent) => {
        let points = 0;
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                points += dfs(neighbor, node);
            }
        }
        // Calculate points for current node
        const option1 = coins[node] - k;
        const option2 = Math.floor(coins[node] / 2);
        
        if (option1 >= option2) {
            points += option1;
            coins[node] = 0; // All coins collected
        } else {
            points += option2;
            coins[node] = Math.floor(coins[node] / 2); // Coins reduced for subtree
        }
        
        return points;
    };
    
    return dfs(0, -1); // Start DFS from root node 0
};
