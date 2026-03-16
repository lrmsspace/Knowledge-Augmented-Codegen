// Source: https://leetcode.com/problems/kth-smallest-element-in-a-bst/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) of all the values of the nodes in the tree.
//
// Example:
// Input: root = [3,1,4,null,2], k = 1
// Output: 1
//
// Constraints:
// The number of nodes in the tree is n.
// 	1 <= k <= n <= 104
// 	0 <= Node.val <= 104
//
//
//  
// Follow up: If the BST is modified often (i.e., we can do insert and delete operations) and you need to find the kth smallest frequently, how would you optimize?
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
int kthSmallest(struct TreeNode* root, int k) {
    struct TreeNode* stack[10000];
    int top = -1;
    struct TreeNode* current = root;
    int count = 0;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        count++;
        if (count == k) {
            return current->val;
        }
        current = current->right;
    }

    return -1; // This line should never be reached if k is valid       
}
