// Source: https://leetcode.com/problems/create-binary-tree-from-descriptions/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array descriptions where descriptions[i] = [parenti, childi, isLefti] indicates that parenti is the parent of childi in a binary tree of unique values. Furthermore,
//
//
// 	If isLefti == 1, then childi is the left child of parenti.
// 	If isLefti == 0, then childi is the right child of parenti.
//
//
// Construct the binary tree described by descriptions and return its root.
//
// The test cases will be generated such that the binary tree is valid.
//
// Example:
// Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
// Output: [50,20,80,15,17,19]
// Explanation: The root node is the node with value 50 since it has no parent.
// The resulting binary tree is shown in the diagram.
//
// Constraints:
// 1 <= descriptions.length <= 104
// 	descriptions[i].length == 3
// 	1 <= parenti, childi <= 105
// 	0 <= isLefti <= 1
// 	The binary tree described by descriptions is valid.
//
// Helpful references (internal KB):
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
//   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
//   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
// - Prüfer code (tree, heap, simulation, greedy)
//   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
//   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
//   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
//   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
//   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
// - Lowest Common Ancestor - Farach-Colton and Bender Algorithm (tree, array, dfs)
//   • When to use: When frequent LCA queries are needed on a static tree, and optimal query time is critical. It's suitable for scenarios requiring O(1) query time after initial preprocessing.
//   • Idea: This algorithm finds the Lowest Common Ancestor (LCA) of two nodes in a tree by reducing the problem to Range Minimum Query (RMQ) on an Euler tour. It preprocesses the tree in O(N) time using DFS to build an array of nodes and their depths, then answers LCA queries in O(1) time.
//   • Invariants: The Euler tour array contains every edge traversed twice, and each node appears at least once.; The depth array stores the correct distance from the root for each node's occurrence in the Euler tour.
//   • Tips: Perform a DFS to construct the Euler tour and depth array.; Store both the node identifier and its depth during the Euler tour.
//   • Pitfalls: Incorrectly defining the start and end indices for the RMQ on the Euler tour.; Off-by-one errors when mapping Euler tour indices to original nodes or depths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* createBinaryTree(int** descriptions, int descriptionsSize, int* descriptionsColSize) {
    int i, j, parent, child, isLeft;
    struct TreeNode *nodes[100001] = {0}; // Assuming values are in the range [1, 100000]
    int hasParent[100001] = {0}; // To track which nodes have parents

    // Create nodes and build the tree
    for (i = 0; i < descriptionsSize; i++) {
        parent = descriptions[i][0];
        child = descriptions[i][1];
        isLeft = descriptions[i][2];

        // Create parent node if it doesn't exist
        if (nodes[parent] == NULL) {
            nodes[parent] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            nodes[parent]->val = parent;
            nodes[parent]->left = NULL;
            nodes[parent]->right = NULL;
        }

        // Create child node if it doesn't exist
        if (nodes[child] == NULL) {
            nodes[child] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            nodes[child]->val = child;
            nodes[child]->left = NULL;
            nodes[child]->right = NULL;
        }

        // Link parent and child
        if (isLeft) {
            nodes[parent]->left = nodes[child];
        } else {
            nodes[parent]->right = nodes[child];
        }

        // Mark child as having a parent
        hasParent[child] = 1;
    }

    // Find the root (the node that has no parent)
    for (i = 1; i <= 100000; i++) {
        if (nodes[i] != NULL && !hasParent[i]) {
            return nodes[i]; // Return the root node
        }
    }

    return NULL; // In case no root is found, though the problem guarantees a valid tree        
}
