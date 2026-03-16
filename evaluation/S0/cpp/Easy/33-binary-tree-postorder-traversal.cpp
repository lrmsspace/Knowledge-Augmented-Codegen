// Source: https://leetcode.com/problems/binary-tree-postorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return the postorder traversal of its nodes' values.
//
// Example:
// Input: root = [1,null,2,3]
//
// Output: [3,2,1]
//
// Explanation:
//
// Constraints:
// The number of the nodes in the tree is in the range [0, 100].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow up: Recursive solution is trivial, could you do it iteratively?
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        stack<TreeNode*> stk;
        stk.push(root);

        while (!stk.empty()) {
            TreeNode* node = stk.top();
            stk.pop();
            result.push_back(node->val);

            if (node->left) {
                stk.push(node->left);
            }
            if (node->right) {
                stk.push(node->right);
            }
        }

        reverse(result.begin(), result.end());
        return result;          
    }
};
