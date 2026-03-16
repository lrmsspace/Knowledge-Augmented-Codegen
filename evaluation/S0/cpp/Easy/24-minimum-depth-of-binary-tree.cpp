// Source: https://leetcode.com/problems/minimum-depth-of-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary tree, find its minimum depth.
//
// The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
//
// Note: A leaf is a node with no children.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: 2
//
// Constraints:
// The number of nodes in the tree is in the range [0, 105].
// 	-1000 <= Node.val <= 1000
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        if (!root->left && !root->right) return 1;

        int leftDepth = INT_MAX, rightDepth = INT_MAX;

        if (root->left) {
            leftDepth = minDepth(root->left);
        }
        if (root->right) {
            rightDepth = minDepth(root->right);
        }

        return 1 + min(leftDepth, rightDepth);          
    }
};
