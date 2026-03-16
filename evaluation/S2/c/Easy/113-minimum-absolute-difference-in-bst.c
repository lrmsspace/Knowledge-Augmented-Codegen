// Source: https://leetcode.com/problems/minimum-absolute-difference-in-bst/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.
//
// Example:
// Input: root = [4,2,6,1,3]
// Output: 1
//
// Constraints:
// The number of nodes in the tree is in the range [2, 104].
// 	0 <= Node.val <= 105
//
//
//  
// Note: This question is the same as 783: https://leetcode.com/problems/minimum-distance-between-bst-nodes/
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
int getMinimumDifference(struct TreeNode* root) {
    int min_diff = 2147483647; // Initialize to maximum integer value
    int prev_val = -1; // To store the value of the previous node in in-order traversal
    struct TreeNode* stack[10000]; // Stack for iterative in-order traversal
    int top = -1; // Stack pointer

    while (top >= 0 || root != NULL) {
        // Traverse to the leftmost node
        while (root != NULL) {
            stack[++top] = root;
            root = root->left;
        }

        // Process the current node
        root = stack[top--];
        if (prev_val != -1) {
            int diff = root->val - prev_val;
            if (diff < min_diff) {
                min_diff = diff; // Update minimum difference
            }
        }
        prev_val = root->val; // Update previous value

        // Move to the right subtree
        root = root->right;
    }

    return min_diff;        
}
