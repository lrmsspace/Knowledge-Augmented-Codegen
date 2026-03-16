// Source: https://leetcode.com/problems/invert-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, invert the tree, and return its root.
//
// Example:
// Input: root = [4,2,7,1,3,6,9]
// Output: [4,7,2,9,6,3,1]
//
// Constraints:
// The number of nodes in the tree is in the range [0, 100].
// 	-100 <= Node.val <= 100
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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        root->left = right;
        root->right = left;

        return root;            
    }
};
