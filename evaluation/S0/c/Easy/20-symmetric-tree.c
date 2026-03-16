// Source: https://leetcode.com/problems/symmetric-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
//
// Example:
// Input: root = [1,2,2,3,4,4,3]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow up: Could you solve it both recursively and iteratively?
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSymmetric(struct TreeNode* root) {
    if (!root) return true;

    struct TreeNode** stack = malloc(sizeof(struct TreeNode*) * 2000);
    int top = -1;

    stack[++top] = root->left;
    stack[++top] = root->right;

    while (top >= 0) {
        struct TreeNode* right = stack[top--];
        struct TreeNode* left = stack[top--];

        if (!left && !right) continue;
        if (!left || !right) {
            free(stack);
            return false;
        }
        if (left->val != right->val) {
            free(stack);
            return false;
        }

        stack[++top] = left->left;
        stack[++top] = right->right;
        stack[++top] = left->right;
        stack[++top] = right->left;
    }

    free(stack);
    return true;        
}
