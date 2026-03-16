// Source: https://leetcode.com/problems/binary-tree-paths/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return all root-to-leaf paths in any order.
//
// A leaf is a node with no children.
//
// Example:
// Input: root = [1,2,3,null,5]
// Output: ["1->2->5","1->3"]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 100].
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        if (!root) return result;

        function<void(TreeNode*, string)> dfs = [&](TreeNode* node, string path) {
            if (!node->left && !node->right) {
                result.push_back(path);
                return;
            }
            if (node->left) {
                dfs(node->left, path + "->" + to_string(node->left->val));
            }
            if (node->right) {
                dfs(node->right, path + "->" + to_string(node->right->val));
            }
        };

        dfs(root, to_string(root->val));
        return result;          
    }
};
