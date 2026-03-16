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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isCompleteTree(struct TreeNode* root) {
    if (!root) return true;

    struct TreeNode* queue[200];
    int front = 0, rear = 0;
    bool end = false;

    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* node = queue[front++];

        if (node) {
            if (end) return false; // Found a non-null node after a null node
            queue[rear++] = node->left;
            queue[rear++] = node->right;
        } else {
            end = true; // Mark that we've seen a null node
        }
    }

    return true;        
}
