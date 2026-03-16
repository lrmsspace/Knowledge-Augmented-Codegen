// Source: https://leetcode.com/problems/make-costs-of-paths-equal-in-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the number of nodes in a perfect binary tree consisting of nodes numbered from 1 to n. The root of the tree is node 1 and each node i in the tree has two children where the left child is the node 2 * i and the right child is 2 * i + 1.
//
// Each node in the tree also has a cost represented by a given 0-indexed integer array cost of size n where cost[i] is the cost of node i + 1. You are allowed to increment the cost of any node by 1 any number of times.
//
// Return the minimum number of increments you need to make the cost of paths from the root to each leaf node equal.
//
// Note:
//
//
// 	A perfect binary tree is a tree where each node, except the leaf nodes, has exactly 2 children.
// 	The cost of a path is the sum of costs of nodes in the path.
//
// Example:
// Input: n = 7, cost = [1,5,2,2,3,3,1]
// Output: 6
// Explanation: We can do the following increments:
// - Increase the cost of node 4 one time.
// - Increase the cost of node 3 three times.
// - Increase the cost of node 7 two times.
// Each path from the root to a leaf will have a total cost of 9.
// The total increments we did is 1 + 3 + 2 = 6.
// It can be shown that this is the minimum answer we can achieve.
//
// Constraints:
// 3 <= n <= 105
// 	n + 1 is a power of 2
// 	cost.length == n
// 	1 <= cost[i] <= 104
//
// Helpful references (internal KB):
// - Sqrt Tree (array, tree, recursion)
//   • When to use: When you need to perform O(1) range queries and support efficient updates (single element or range) on an array, leveraging a hierarchical decomposition.
//   • Idea: A Sqrt Tree is a data structure that supports O(1) range queries and efficient updates on an array. It recursively decomposes the array into blocks and layers, using precomputed information and bitwise operations to quickly answer queries and propagate updates.
//   • Invariants: Each element is part of exactly one block at each layer of the Sqrt Tree.; The highest differing bit between `l` and `r` identifies the specific layer for processing `q(l, r)`.
//   • Tips: Precompute highest bit for efficient layer selection.; Decompose queries into intra-block and inter-block segments.
//   • Pitfalls: Naive updates can result in O(N) complexity per update.; High memory consumption due to multiple layers of precomputed arrays.
// - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
//   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
//   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
//   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
//   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
//   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[]} cost
 * @return {number}
 */ 
var minIncrements = function(n, cost) {
    let increments = 0;
    for (let i = n - 1; i > 0; i -= 2) {
        const leftChildCost = cost[i - 1];
        const rightChildCost = cost[i];
        const parentCost = cost[Math.floor((i - 1) / 2)];
        const maxChildCost = Math.max(leftChildCost, rightChildCost);
        if (parentCost < maxChildCost) {
            increments += maxChildCost - parentCost;
            cost[Math.floor((i - 1) / 2)] = maxChildCost;
        }
    }
    return increments;
};
