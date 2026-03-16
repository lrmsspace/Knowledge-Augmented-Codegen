// Source: https://leetcode.com/problems/univalued-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// A binary tree is uni-valued if every node in the tree has the same value.
//
// Given the root of a binary tree, return true if the given tree is uni-valued, or false otherwise.
//
// Example:
// Input: root = [1,1,1,1,1,null,1]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 100].
// 	0 <= Node.val < 100
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isUnivalTree(struct TreeNode* root) {
    if (!root) {
        return true;
    }
    if (root->left && root->left->val != root->val) {
        return false;
    }
    if (root->right && root->right->val != root->val) {
        return false;
    }
    return isUnivalTree(root->left) && isUnivalTree(root->right);       
}
