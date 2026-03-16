// Source: https://leetcode.com/problems/find-subtree-sizes-after-changes/   |   Difficulty: Medium
//
// Problem Description:
// You are given a tree rooted at node 0 that consists of n nodes numbered from 0 to n - 1. The tree is represented by an array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
//
// You are also given a string s of length n, where s[i] is the character assigned to node i.
//
// We make the following changes on the tree one time simultaneously for all nodes x from 1 to n - 1:
//
//
// 	Find the closest node y to node x such that y is an ancestor of x, and s[x] == s[y].
// 	If node y does not exist, do nothing.
// 	Otherwise, remove the edge between x and its current parent and make node y the new parent of x by adding an edge between them.
//
//
// Return an array answer of size n where answer[i] is the size of the subtree rooted at node i in the final tree.
//
// Example:
// Input: parent = [-1,0,0,1,1,1], s = "abaabc"
//
// Output: [6,3,1,1,1,1]
//
// Explanation:
//
// The parent of node 3 will change from node 1 to node 0.
//
// Constraints:
// n == parent.length == s.length
// 	1 <= n <= 105
// 	0 <= parent[i] <= n - 1 for all i >= 1.
// 	parent[0] == -1
// 	parent represents a valid tree.
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
// - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
//   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
//   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
//   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
//   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
//   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
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
int* findSubtreeSizes(int* parent, int parentSize, char* s, int* returnSize) {
    int* subtreeSizes = (int*)calloc(parentSize, sizeof(int));  
    // Step 1: Build the tree as an adjacency list
    int** tree = (int**)malloc(parentSize * sizeof(int*));
    int* treeSizes = (int*)calloc(parentSize, sizeof(int)); // To track the number of children for each node
    for (int i = 0; i < parentSize; i++) {
        tree[i] = (int*)malloc(parentSize * sizeof(int)); // Allocate maximum possible size for children
    }
    for (int i = 1; i < parentSize; i++) {
        int p = parent[i];
        tree[p][treeSizes[p]++] = i; // Add child to parent's list and increment size
    }
    // Step 2: DFS to calculate subtree sizes
    void dfs(int node) {
        subtreeSizes[node] = 1; // Count the node itself
        for (int i = 0; i < treeSizes[node]; i++) {
            int child = tree[node][i];
            dfs(child);
            subtreeSizes[node] += subtreeSizes[child]; // Add child's subtree size
        }
    }
    dfs(0); // Start DFS from the root node
    // Step 3: Handle the changes based on string s
    for (int i = 1; i < parentSize; i++) {
        int currentParent = parent[i];
        char currentChar = s[i];
        int ancestor = currentParent;
        while (ancestor != -1 && s[ancestor] != currentChar) {
            ancestor = parent[ancestor]; // Move up to the next ancestor
        }
        if (ancestor != -1) {
            // We found an ancestor with the same character, we need to change the parent
            subtreeSizes[currentParent] -= subtreeSizes[i]; // Remove the subtree size from the old parent
            subtreeSizes[ancestor] += subtreeSizes[i]; // Add the subtree size to the new parent
            parent[i] = ancestor; // Update the parent of node i
        }
    }
    *returnSize = parentSize;
    return subtreeSizes;
    
}
