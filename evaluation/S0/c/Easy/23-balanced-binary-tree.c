// Source: https://leetcode.com/problems/balanced-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary tree, determine if it is height-balanced.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [0, 5000].
// 	-104 <= Node.val <= 104
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isBalanced(struct TreeNode* root) {
    bool balanced = true;

    int height(struct TreeNode* node) {
        if (!node || !balanced) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (abs(leftHeight - rightHeight) > 1) {
            balanced = false;
        }

        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    height(root);
    return balanced;        
}
