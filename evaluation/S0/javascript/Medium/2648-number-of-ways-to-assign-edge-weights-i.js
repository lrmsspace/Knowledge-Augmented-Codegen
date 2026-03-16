// Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
//
// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
//
// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
//
// Select any one node x at the maximum depth. Return the number of ways to assign edge weights in the path from node 1 to x such that its total cost is odd.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note: Ignore all edges not in the path from node 1 to x.
//
// Example:
// Input: edges = [[1,2]]
//
// Output: 1
//
// Explanation:
//
//
// 	The path from Node 1 to Node 2 consists of one edge (1 → 2).
// 	Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	1 <= ui, vi <= n
// 	edges represents a valid tree.
//

/**
 * @param {number[][]} edges
 * @return {number}
 */
var assignEdgeWeights = function(edges) {
    const graph = Array.from({ length: edges.length + 1 }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    const mod = 1e9 + 7;
    const dfs = (node, parent) => {
        let oddCount = 0;
        let evenCount = 0;
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                const [childOdd, childEven] = dfs(neighbor, node);
                oddCount = (oddCount + childEven) % mod;
                evenCount = (evenCount + childOdd) % mod;
            }
        }
        if (oddCount === 0 && evenCount === 0) {
            return [1, 1]; // Leaf node can be assigned either weight
        }
        return [oddCount, evenCount];
    };
    const [oddWays, evenWays] = dfs(1, -1);
    return oddWays % mod;   
}           
