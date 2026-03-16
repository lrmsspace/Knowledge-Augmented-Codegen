// Source: https://leetcode.com/problems/increasing-order-search-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only one right child.
//
// Example:
// Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
// Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
//
// Constraints:
// The number of nodes in the given tree will be in the range [1, 100].
// 	0 <= Node.val <= 1000
//
// Helpful references (internal KB):
// - Binary Search Trees
//  (tree, enumeration)
//   • When to use: Use when you need to store ordered data in a hierarchical structure that allows for efficient searching, insertion, and deletion operations. It is suitable for dynamic datasets where elements frequently change while maintaining sorted order.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree data structure where each node has a key, and all keys in the left subtree are less than the node's key, while all keys in the right subtree are greater. Basic operations like search, insertion, and deletion typically have an average time complexity of O(log N) but can degrade to O(N) in the worst case.
//   • Invariants: For every node N, if L is in N's left subtree, then L.key < N.key.; For every node N, if R is in N's right subtree, then R.key > N.key.
//   • Tips: Understand the recursive definition for traversal and operations.; Handle edge cases like empty tree, single node, or leaf nodes carefully.
//   • Pitfalls: Unbalanced trees can lead to O(N) worst-case performance for all operations.; Incorrect handling of duplicate keys can lead to data loss or incorrect structure.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, lca)
//   • When to use: Use this technique for efficiently answering multiple Range Minimum Queries on a static array, especially when an asymptotically optimal O(1) query time solution is required.
//   • Idea: This algorithm solves the static Range Minimum Query problem by first constructing a Cartesian tree from the input array, then reducing RMQ queries to Lowest Common Ancestor queries on this tree. It achieves an optimal O(N) preprocessing time and O(1) query time.
//   • Invariants: For any node `u` in the Cartesian tree, `value(u)` is the minimum among all values in the original array segment represented by `u`'s subtree.; The in-order traversal of the Cartesian tree nodes' original array indices yields the original array `A`'s indices in increasing order.
//   • Tips: Construct the Cartesian tree efficiently in O(N) time, typically using a stack-based approach.; The value of the LCA of two nodes in the Cartesian tree corresponds to the minimum in the original array range between their indices.
//   • Pitfalls: Incorrectly building the Cartesian tree, especially when handling duplicate values or edge cases like empty arrays.; The Farach-Colton and Bender LCA algorithm is complex to implement and often requires significant effort.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
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
struct TreeNode* increasingBST(struct TreeNode* root) {
    if (root == NULL) {
        return NULL;
    }

    struct TreeNode* left = increasingBST(root->left);
    struct TreeNode* right = increasingBST(root->right);

    root->left = NULL;
    root->right = right;

    if (left == NULL) {
        return root;
    }

    struct TreeNode* tail = left;
    while (tail->right != NULL) {
        tail = tail->right;
    }
    tail->right = root;

    return left;        
}
