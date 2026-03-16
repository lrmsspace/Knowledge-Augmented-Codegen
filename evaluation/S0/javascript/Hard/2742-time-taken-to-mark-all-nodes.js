// Source: https://leetcode.com/problems/time-taken-to-mark-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
//
// Initially, all nodes are unmarked. For each node i:
//
//
// 	If i is odd, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 1.
// 	If i is even, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 2.
//
//
// Return an array times where times[i] is the time when all nodes get marked in the tree, if you mark node i at time t = 0.
//
// Note that the answer for each times[i] is independent, i.e. when you mark node i all other nodes are unmarked.
//
// Example:
// Input: edges = [[0,1],[0,2]]
//
// Output: [2,4,3]
//
// Explanation:
//
//
//
//
// 	For i = 0:
//
// 	
// 		Node 1 is marked at t = 1, and Node 2 at t = 2.
// 	
// 	
// 	For i = 1:
// 	
// 		Node 0 is marked at t = 2, and Node 2 at t = 4.
// 	
// 	
// 	For i = 2:
// 	
// 		Node 0 is marked at t = 2, and Node 1 at t = 3.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= edges[i][0], edges[i][1] <= n - 1
// 	The input is generated such that edges represents a valid tree.
//

/**
 * @param {number[][]} edges
 * @return {number[]}
 */
var timeTaken = function(edges) {   
    const n = edges.length + 1;
    const graph = Array.from({ length: n }, () => []);
    
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    
    const dp = Array.from({ length: n }, () => [0, 0]);
    
    const dfs = (node, parent) => {
        for (const neighbor of graph[node]) {
            if (neighbor === parent) continue;
            dfs(neighbor, node);
            dp[node][0] = Math.max(dp[node][0], dp[neighbor][1] + 1);
            dp[node][1] = Math.max(dp[node][1], dp[neighbor][0] + 1);
        }
    };
    
    dfs(0, -1);
    
    const result = Array(n).fill(0);
    
    const reroot = (node, parent, up0, up1) => {
        const prefixMax0 = [];
        const prefixMax1 = [];
        const suffixMax0 = [];
        const suffixMax1 = [];
        
        let max0 = up0;
        let max1 = up1;
        
        for (const neighbor of graph[node]) {
            if (neighbor === parent) continue;
            prefixMax0.push(max0);
            prefixMax1.push(max1);
            max0 = Math.max(max0, dp[neighbor][1] + 1);
            max1 = Math.max(max1, dp[neighbor][0] + 1);
        }
        
        max0 = up0;
        max1 = up1;
        
        for (let i = graph[node].length - 1; i >= 0; i--) {
            const neighbor = graph[node][i];
            if (neighbor === parent) continue;
            suffixMax0[i] = max0;
            suffixMax1[i] = max1;
            max0 = Math.max(max0, dp[neighbor][1] + 1);
            max1 = Math.max(max1, dp[neighbor][0] + 1);
        }
        
        
};
