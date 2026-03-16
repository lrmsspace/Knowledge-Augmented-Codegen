// Source: https://leetcode.com/problems/minimum-distance-between-bst-nodes/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a Binary Search Tree (BST), return the minimum difference between the values of any two different nodes in the tree.
//
// Example:
// Input: root = [4,2,6,1,3]
// Output: 1
//
// Constraints:
// The number of nodes in the tree is in the range [2, 100].
// 	0 <= Node.val <= 105
//
//
//  
// Note: This question is the same as 530: https://leetcode.com/problems/minimum-absolute-difference-in-bst/
//
// Helpful references (internal KB):
// - N/A
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
int minDiffInBST(struct TreeNode* root) {
    int min_diff = 100001; // Given constraints: 0 <= Node.val <= 10^5
    int prev_val = -1; // To track the value of the previous node in in-order traversal

    // Helper function for in-order traversal
    void inorder(struct TreeNode* node) {
        if (!node) return;

        // Traverse left subtree
        inorder(node->left);

        // Process current node
        if (prev_val != -1) {
            int diff = node->val - prev_val;
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
        prev_val = node->val;

        // Traverse right subtree
        inorder(node->right);
    }

    inorder(root);
    return min_diff;        
}
