// Source: https://leetcode.com/problems/find-bottom-left-tree-value/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the leftmost value in the last row of the tree.
//
// Example:
// Input: root = [2,1,3]
// Output: 1
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-231 <= Node.val <= 231 - 1
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
    int findBottomLeftValue(TreeNode* root) {
        if (!root) return -1;

        queue<TreeNode*> q;
        q.push(root);
        int leftmostValue = root->val;

        while (!q.empty()) {
            int levelSize = q.size();
            leftmostValue = q.front()->val; // The first node in the current level

            for (int i = 0; i < levelSize; ++i) {
                TreeNode* currentNode = q.front();
                q.pop();

                if (currentNode->left) {
                    q.push(currentNode->left);
                }
                if (currentNode->right) {
                    q.push(currentNode->right);
                }
            }
        }

        return leftmostValue;           
    }
};
