// Source: https://leetcode.com/problems/maximum-depth-of-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return its maximum depth.
//
// A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: 3
//
// Constraints:
// The number of nodes in the tree is in the range [0, 104].
// 	-100 <= Node.val <= 100
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int left_depth = maxDepth(root->left);
    int right_depth = maxDepth(root->right);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;       
}
