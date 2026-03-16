// Source: https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/   |   Difficulty: Hard
//
// Problem Description:
// There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively. You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
//
// You must connect one node from the first tree with another node from the second tree with an edge.
//
// Return the minimum possible diameter of the resulting tree.
//
// The diameter of a tree is the length of the longest path between any two nodes in the tree.
//
// Example:
// Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
//
// Output: 3
//
// Explanation:
//
// We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.
//
// Constraints:
// 1 <= n, m <= 105
// 	edges1.length == n - 1
// 	edges2.length == m - 1
// 	edges1[i].length == edges2[i].length == 2
// 	edges1[i] = [ai, bi]
// 	0 <= ai, bi < n
// 	edges2[i] = [ui, vi]
// 	0 <= ui, vi < m
// 	The input is generated such that edges1 and edges2 represent valid trees.
//
// Helpful references (internal KB):
// - Lowest Common Ancestor - Farach-Colton and Bender Algorithm (tree, array, dfs)
//   • When to use: When frequent LCA queries are needed on a static tree, and optimal query time is critical. It's suitable for scenarios requiring O(1) query time after initial preprocessing.
//   • Idea: This algorithm finds the Lowest Common Ancestor (LCA) of two nodes in a tree by reducing the problem to Range Minimum Query (RMQ) on an Euler tour. It preprocesses the tree in O(N) time using DFS to build an array of nodes and their depths, then answers LCA queries in O(1) time.
//   • Invariants: The Euler tour array contains every edge traversed twice, and each node appears at least once.; The depth array stores the correct distance from the root for each node's occurrence in the Euler tour.
//   • Tips: Perform a DFS to construct the Euler tour and depth array.; Store both the node identifier and its depth during the Euler tour.
//   • Pitfalls: Incorrectly defining the start and end indices for the RMQ on the Euler tour.; Off-by-one errors when mapping Euler tour indices to original nodes or depths.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} edges1
 * @param {number[][]} edges2
 * @return {number}
 */
var minimumDiameterAfterMerge = function(edges1, edges2) {
    function bfs(start, graph) {
        const queue = [start];
        const visited = new Set([start]);
        let lastNode = start;
        while (queue.length > 0) {
            const current = queue.shift();
            for (const neighbor of graph[current] || []) {
                if (!visited.has(neighbor)) {
                    visited.add(neighbor);
                    queue.push(neighbor);
                    lastNode = neighbor;
                }
            }
        }
        return lastNode;
    };
    
    function getDiameter(edges) {
        const graph = {};
        for (const [u, v] of edges) {
            if (!graph[u]) graph[u] = [];
            if (!graph[v]) graph[v] = [];
            graph[u].push(v);
            graph[v].push(u);
        }
        const farthestNode = bfs(0, graph);
        return bfs(farthestNode, graph);
    }

    const diameter1 = getDiameter(edges1);
    const diameter2 = getDiameter(edges2);
    return diameter1 + diameter2 + 1;
};
