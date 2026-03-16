// Source: https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with n nodes, where each node is uniquely assigned a value from 1 to n. You are also given a sequence of n values voyage, which is the desired pre-order traversal of the binary tree.
//
// Any node in the binary tree can be flipped by swapping its left and right subtrees. For example, flipping node 1 will have the following effect:
//
// Flip the smallest number of nodes so that the pre-order traversal of the tree matches voyage.
//
// Return a list of the values of all flipped nodes. You may return the answer in any order. If it is impossible to flip the nodes in the tree to make the pre-order traversal match voyage, return the list [-1].
//
// Example:
// Input: root = [1,2], voyage = [2,1]
// Output: [-1]
// Explanation: It is impossible to flip the nodes such that the pre-order traversal matches voyage.
//
// Constraints:
// The number of nodes in the tree is n.
// 	n == voyage.length
// 	1 <= n <= 100
// 	1 <= Node.val, voyage[i] <= n
// 	All the values in the tree are unique.
// 	All the values in voyage are unique.
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
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        vector<int> result;
        int index = 0;

        function<bool(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return true;
            if (node->val != voyage[index++]) return false;

            if (node->left && node->left->val != voyage[index]) {
                result.push_back(node->val);
                return dfs(node->right) && dfs(node->left);
            } else {
                return dfs(node->left) && dfs(node->right);
            }
        };

        if (!dfs(root)) return {-1};
        return result;          
    }
};
