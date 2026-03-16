// Source: https://leetcode.com/problems/validate-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, determine if it is a valid binary search tree (BST).
//
// A valid BST is defined as follows:
//
//
// 	The left subtree of a node contains only nodes with keys strictly less than the node's key.
// 	The right subtree of a node contains only nodes with keys strictly greater than the node's key.
// 	Both the left and right subtrees must also be binary search trees.
//
// Example:
// Input: root = [2,1,3]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-231 <= Node.val <= 231 - 1
//
// Helpful references (internal KB):
// - Binary Search Trees
//  (tree, recursion)
//   • When to use: When you need to store ordered data that allows efficient searching, insertion, and deletion while maintaining sorted order. It's suitable for dynamic datasets where elements frequently change.
//   • Idea: A Binary Search Tree (BST) is a node-based binary tree where keys in the left subtree are smaller than the node's key, and keys in the right subtree are larger. Operations like search, insert, and delete typically run in O(log N) average time and O(N) worst-case.
//   • Invariants: For any node, all keys in its left subtree are strictly less than its key.; For any node, all keys in its right subtree are strictly greater than its key.
//   • Tips: Maintain the BST property: left child < parent < right child.; Recursion simplifies many operations like search, insert, and traversal.
//   • Pitfalls: Unbalanced trees can degrade performance to O(N) for all operations.; Incorrect handling of duplicate keys can break BST properties or lead to data loss.
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: When searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It is efficient for functions where direct differentiation or analytical solutions are complex.
//   • Idea: Ternary search is an algorithm that efficiently finds the extremum of a unimodal function within a given interval by repeatedly narrowing the search space. It typically achieves a logarithmic time complexity, O(log N), where N is the interval size.
//   • Invariants: The extremum of the unimodal function always lies within the current search interval [l, r].; The function value at m1 is compared with m2 to narrow the interval while preserving unimodality.
//   • Tips: Ensure the function is strictly unimodal within the search interval.; Handle discrete intervals carefully, especially the stopping condition (r - l) < 3.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Incorrect stopping conditions can lead to infinite loops or suboptimal answers.
// - Lowest Common Ancestor (array, min-window)
//   • When to use: Use when needing to find the lowest common ancestor of two nodes in a tree efficiently for multiple queries. This approach is ideal when the tree is static and preprocessing is acceptable.
//   • Idea: This method finds the LCA by converting the problem into a Range Minimum Query on an Euler tour of the tree's depths. It preprocesses the tree in O(N log N) or O(N) time and answers queries in O(log N) or O(1) time.
//   • Invariants: The Euler tour array correctly records nodes in DFS entry/exit order.; The depth array stores the correct depth for each node in the Euler tour.
//   • Tips: Perform a DFS to construct the Euler tour and depth array.; Store the first occurrence index of each node in the Euler tour.
//   • Pitfalls: Incorrectly constructing the Euler tour or depth array.; Off-by-one errors when mapping Euler tour indices to original nodes.
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
bool isValidBST(struct TreeNode* root) {
    // Helper function to validate the BST properties recursively.
    bool validate(struct TreeNode* node, long min, long max) {
        // An empty node is a valid BST.
        if (node == NULL) {
            return true;
        }
        // Check if the current node's value is within the valid range.
        if (node->val <= min || node->val >= max) {
            return false;
        }
        // Recursively validate the left and right subtrees with updated ranges.
        return validate(node->left, min, node->val) && validate(node->right, node->val, max);
    }

    // Start validation with the entire range of valid values for a BST.
    return validate(root, LONG_MIN, LONG_MAX);      
}
