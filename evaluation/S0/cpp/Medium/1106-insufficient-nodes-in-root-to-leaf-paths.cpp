// Source: https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree and an integer limit, delete all insufficient nodes in the tree simultaneously, and return the root of the resulting binary tree.
//
// A node is insufficient if every root to leaf path intersecting this node has a sum strictly less than limit.
//
// A leaf is a node with no children.
//
// Example:
// Input: root = [1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14], limit = 1
// Output: [1,2,3,4,null,null,7,8,9,null,14]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 5000].
// 	-105 <= Node.val <= 105
// 	-109 <= limit <= 109
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
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        if (!root) return nullptr;

        root->left = sufficientSubset(root->left, limit - root->val);
        root->right = sufficientSubset(root->right, limit - root->val);

        if (!root->left && !root->right) {
            return (root->val < limit) ? nullptr : root;
        }

        return root;            
    }
};
