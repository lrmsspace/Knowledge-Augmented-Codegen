// Source: https://leetcode.com/problems/maximum-width-of-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the maximum width of the given tree.
//
// The maximum width of a tree is the maximum width among all levels.
//
// The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
//
// It is guaranteed that the answer will in the range of a 32-bit signed integer.
//
// Example:
// Input: root = [1,3,2,5,3,null,9]
// Output: 4
// Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).
//
// Constraints:
// The number of nodes in the tree is in the range [1, 3000].
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
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;

        unsigned long long maxWidth = 0;
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 1});

        while (!q.empty()) {
            int levelSize = q.size();
            unsigned long long leftMost = q.front().second;
            unsigned long long rightMost = leftMost; // Initialize rightMost

            for (int i = 0; i < levelSize; ++i) {
                auto [node, index] = q.front();
                q.pop();
                rightMost = index; // Update rightMost to the current node's index

                if (node->left) {
                    q.push({node->left, index * 2});
                }
                if (node->right) {
                    q.push({node->right, index * 2 + 1});
                }
            }

            maxWidth = max(maxWidth, rightMost - leftMost + 1);
        }

        return static_cast<int>(maxWidth);          
    }
};
