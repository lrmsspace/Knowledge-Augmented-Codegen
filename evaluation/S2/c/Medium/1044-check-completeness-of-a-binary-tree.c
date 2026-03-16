// Source: https://leetcode.com/problems/check-completeness-of-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, determine if it is a complete binary tree.
//
// In a complete binary tree, every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
//
// Example:
// Input: root = [1,2,3,4,5,6]
// Output: true
// Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 100].
// 	1 <= Node.val <= 1000
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
bool isCompleteTree(struct TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    
    struct TreeNode* queue[100]; // Queue to hold nodes for level order traversal
    int front = 0, rear = 0; // Queue pointers
    bool end = false; // Flag to indicate if we've encountered a NULL node
    
    // Enqueue the root node
    queue[rear++] = root;
    
    while (front < rear) {
        struct TreeNode* current = queue[front++]; // Dequeue the front node
        
        if (current == NULL) {
            end = true; // We've encountered a NULL node, set the flag
        } else {
            if (end) {
                return false; // If we encounter a non-NULL node after a NULL node, it's not complete
            }
            // Enqueue left and right children
            queue[rear++] = current->left;
            queue[rear++] = current->right;
        }
    }
    
    return true; // If we finish processing without issues, it's complete       
}
