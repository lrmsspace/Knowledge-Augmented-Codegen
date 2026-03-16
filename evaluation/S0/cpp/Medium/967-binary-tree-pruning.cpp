// Source: https://leetcode.com/problems/binary-tree-pruning/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
//
// A subtree of a node node is node plus every node that is a descendant of node.
//
// Example:
// Input: root = [1,null,0,0,1]
// Output: [1,null,0,null,1]
// Explanation: 
// Only the red nodes satisfy the property "every subtree not containing a 1".
// The diagram on the right represents the answer.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 200].
// 	Node.val is either 0 or 1.
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
    TreeNode* pruneTree(TreeNode* root) {
        if (!root) return nullptr;

        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);

        if (root->val == 0 && !root->left && !root->right) {
            return nullptr;
        }

        return root;            
    }
};
