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
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
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
    // This problem can be solved using a Disjoint Set Union (DSU) data structure to manage the changes in the tree structure after the simultaneous updates. We will also need to calculate the subtree sizes after all changes have been applied.

    // Step 1: Initialize DSU and subtree sizes
    int* dsu = (int*)malloc(parentSize * sizeof(int));
    int* size = (int*)malloc(parentSize * sizeof(int));
    for (int i = 0; i < parentSize; i++) {
        dsu[i] = i; // Each node is initially its own parent in DSU
        size[i] = 1; // Each node is initially a subtree of size 1
    }

    // Step 2: Process each node from 1 to n - 1
    for (int x = 1; x < parentSize; x++) {
        int y = parent[x];
        while (y != -1 && s[x] != s[y]) {
            y = parent[y]; // Move up to find the closest ancestor with the same character
        }
        if (y != -1) {
            // If such an ancestor exists, we need to union x with y in DSU
            int rootX = find(dsu, x);
            int rootY = find(dsu, y);
            if (rootX != rootY) {
                // Union by size
                if (size[rootX] < size[rootY]) {
                    dsu[rootX] = rootY;
                    size[rootY] += size[rootX];
                } else {
                    dsu[rootY] = rootX;
                    size[rootX] += size[rootY];
                }
            }
        }
    }

    // Step 3: Prepare the result array with subtree sizes
    int* answer = (int*)malloc(parentSize * sizeof(int));
    for (int i = 0; i < parentSize; i++) {
        answer[i] = size[find(dsu, i)]; // Get the size of the subtree for each node
    }

    // Clean up and return results
    free(dsu);
    free(size);
    *returnSize = parentSize;
    return answer;      
}
