// Source: https://leetcode.com/problems/binary-tree-maximum-path-sum/   |   Difficulty: Hard
//
// Problem Description:
// A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
//
// The path sum of a path is the sum of the node's values in the path.
//
// Given the root of a binary tree, return the maximum path sum of any non-empty path.
//
// Example:
// Input: root = [1,2,3]
// Output: 6
// Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 3 * 104].
// 	-1000 <= Node.val <= 1000
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Heavy-light decomposition (tree, array, dfs, divide-and-conquer, tree-dp)
//   • When to use: When you need to efficiently perform path queries or updates on a tree, transforming tree paths into linear segments for data structures like segment trees.
//   • Idea: Heavy-light decomposition partitions a tree into disjoint heavy paths, ensuring any root-to-node path crosses at most O(log N) heavy paths. This reduces tree path queries to segment operations, typically achieving O(log^2 N) or O(log N) complexity.
//   • Invariants: Every node is part of exactly one heavy path.; Traversing from any node to the root involves at most O(log N) heavy path switches.
//   • Tips: Precompute subtree sizes for all nodes to identify heavy edges.; Map heavy paths to contiguous array segments for efficient range queries.
//   • Pitfalls: Misidentifying heavy edges or having more than one heavy child per node.; Off-by-one errors when converting tree path segments to array indices.
// - Heavy-light decomposition (tree, segment-tree, lca, dfs)
//   • When to use: When you need to perform path queries or updates on a tree efficiently, often involving operations like sum, min, max, or XOR on edges/nodes along a path. It transforms tree paths into linear segments for data structure application.
//   • Idea: Heavy-light decomposition partitions a tree into disjoint heavy paths and light edges, allowing tree path operations to be performed efficiently using data structures like segment trees. It typically achieves O(log^2 N) or O(log N) complexity per query/update after O(N log N) or O(N) preprocessing.
//   • Invariants: Each node belongs to exactly one heavy path.; Moving from a node to its parent via a light edge reduces the subtree size by at least half.
//   • Tips: Perform two DFS traversals: one for subtree sizes and parent pointers, another for heavy/light edges and path IDs.; Map tree nodes to a 1D array for segment tree operations based on their position in heavy paths.
//   • Pitfalls: Incorrectly identifying heavy edges (largest subtree size) during the first DFS.; Off-by-one errors when mapping nodes to segment tree indices or handling path boundaries.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        dfs(root, maxSum);
        return maxSum;          
    }
};
