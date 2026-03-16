// Source: https://leetcode.com/problems/maximum-score-after-applying-operations-on-a-tree/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// You are also given a 0-indexed integer array values of length n, where values[i] is the value associated with the ith node.
//
// You start with a score of 0. In one operation, you can:
//
//
// 	Pick any node i.
// 	Add values[i] to your score.
// 	Set values[i] to 0.
//
//
// A tree is healthy if the sum of values on the path from the root to any leaf node is different than zero.
//
// Return the maximum score you can obtain after performing these operations on the tree any number of times so that it remains healthy.
//
// Example:
// Input: edges = [[0,1],[0,2],[0,3],[2,4],[4,5]], values = [5,2,5,2,1,1]
// Output: 11
// Explanation: We can choose nodes 1, 2, 3, 4, and 5. The value of the root is non-zero. Hence, the sum of values on the path from the root to any leaf is different than zero. Therefore, the tree is healthy and the score is values[1] + values[2] + values[3] + values[4] + values[5] = 11.
// It can be shown that 11 is the maximum score obtainable after any number of operations on the tree.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	values.length == n
// 	1 <= values[i] <= 109
// 	The input is generated such that edges represents a valid tree.
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Maximum flow - Push-relabel method improved (graph, array, greedy, bfs)
//   • When to use: Use this for maximum flow problems on graphs where an optimized push-relabel approach is required. It improves performance by prioritizing vertices with the greatest height for push and relabel operations.
//   • Idea: This algorithm is an optimized variant of the push-relabel maximum flow method, which improves efficiency by always selecting the vertex with the greatest height that has excess flow. This specific vertex selection strategy leads to a better theoretical time complexity, typically O(V^2 * sqrt(E)) or O(V^3) depending on implementation details.
//   • Invariants: For any edge (u, v) in the residual graph, h(u) <= h(v) + 1.; The total excess flow in the network is always non-negative.
//   • Tips: Always select the active vertex with the highest current height.; Maintain a data structure (e.g., buckets or lists) to quickly find highest-height vertices.
//   • Pitfalls: Incorrectly managing the list of highest-height vertices.; Failing to update residual capacities after a push operation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} edges
 * @param {number[]} values
 * @return {number}
 */
var maximumScoreAfterOperations = function(edges, values) {
    const n = values.length;
    const graph = Array.from({ length: n }, () => []);
    
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    
    let maxScore = 0;
    
    function dfs(node, parent) {
        let score = 0;
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                score += dfs(neighbor, node);
            }
        }
        if (score + values[node] > 0) {
            maxScore += values[node];
            return score + values[node];
        }
        return score;
    }
    
    dfs(0, -1);
    
    return maxScore;
};
