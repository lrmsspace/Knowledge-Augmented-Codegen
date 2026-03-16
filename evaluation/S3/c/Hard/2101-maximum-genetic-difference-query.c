// Source: https://leetcode.com/problems/maximum-genetic-difference-query/   |   Difficulty: Hard
//
// Problem Description:
// There is a rooted tree consisting of n nodes numbered 0 to n - 1. Each node's number denotes its unique genetic value (i.e. the genetic value of node x is x). The genetic difference between two genetic values is defined as the bitwise-XOR of their values. You are given the integer array parents, where parents[i] is the parent for node i. If node x is the root of the tree, then parents[x] == -1.
//
// You are also given the array queries where queries[i] = [nodei, vali]. For each query i, find the maximum genetic difference between vali and pi, where pi is the genetic value of any node that is on the path between nodei and the root (including nodei and the root). More formally, you want to maximize vali XOR pi.
//
// Return an array ans where ans[i] is the answer to the ith query.
//
// Example:
// Input: parents = [-1,0,1,1], queries = [[0,2],[3,2],[2,5]]
// Output: [2,3,7]
// Explanation: The queries are processed as follows:
// - [0,2]: The node with the maximum genetic difference is 0, with a difference of 2 XOR 0 = 2.
// - [3,2]: The node with the maximum genetic difference is 1, with a difference of 2 XOR 1 = 3.
// - [2,5]: The node with the maximum genetic difference is 2, with a difference of 5 XOR 2 = 7.
//
// Constraints:
// 2 <= parents.length <= 105
// 	0 <= parents[i] <= parents.length - 1 for every node i that is not the root.
// 	parents[root] == -1
// 	1 <= queries.length <= 3 * 104
// 	0 <= nodei <= parents.length - 1
// 	0 <= vali <= 2 * 105
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to find the Lowest Common Ancestor for multiple pairs of nodes in a tree, and all queries are known beforehand. It's an efficient offline approach for batch processing LCA queries.
//   • Idea: Tarjan's offline LCA algorithm uses a Depth-First Search (DFS) traversal combined with a Union-Find data structure to answer all LCA queries efficiently. It processes N nodes and Q queries in O(N + Q * alpha(N)) time, where alpha is the inverse Ackermann function.
//   • Invariants: After visiting a node 'u' and all its children, 'u' is marked as visited.; For any node 'v' whose subtree has been fully processed, 'find_set(v)' returns the representative of 'v''s component.
//   • Tips: Mark nodes as visited during DFS to track processed subtrees.; Use Union-Find's union operation to merge child subtrees with their parent after processing.
//   • Pitfalls: Forgetting to mark nodes as visited, leading to incorrect LCA identification.; Incorrectly updating the 'ancestor' array or 'find_set' logic in Union-Find.
// - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
//   • When to use: Use when you need to answer multiple Lowest Common Ancestor (LCA) queries on a static tree, and all queries are available before processing.
//   • Idea: Tarjan's off-line LCA algorithm efficiently computes the Lowest Common Ancestor for multiple pairs of nodes in a tree using a single Depth-First Search traversal combined with a Disjoint Set Union data structure, achieving nearly linear time complexity.
//   • Invariants: When DFS is at node `v`, all its children's subtrees have been fully processed and merged into `v`'s DSU set.; For any node `x` whose DFS has completed, `ancestor[find_set(x)]` stores an ancestor of `x` on the path to the root.
//   • Tips: Initialize each node as its own set in DSU with itself as the ancestor.; Process queries for a node only after its children's subtrees are fully processed.
//   • Pitfalls: Not suitable for online LCA queries or dynamic tree structures.; Incorrectly updating the `ancestor` array in the DSU can lead to wrong LCAs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxGeneticDifference(int* parents, int parentsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    *returnSize = queriesSize;
    int* results = (int*)malloc(queriesSize * sizeof(int)); // Allocate memory for results
    // Implement a Trie to store the genetic values along the path from root to the current node
    // Perform a DFS traversal of the tree, inserting and removing genetic values from the Trie as you go down and up the tree
    // For each query, compute the maximum genetic difference using the Trie and store it in results
    return results;
}
    