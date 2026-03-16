// Source: https://leetcode.com/problems/deepest-leaves-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the sum of values of its deepest leaves.
//
// Example:
// Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
// Output: 15
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	1 <= Node.val <= 100
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
    int deepestLeavesSum(TreeNode* root) {
        if (!root) return 0;

        queue<TreeNode*> q;
        q.push(root);
        int deepestSum = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            deepestSum = 0; // Reset sum for the current level

            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                deepestSum += node->val;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }

        return deepestSum;          
    }
};
