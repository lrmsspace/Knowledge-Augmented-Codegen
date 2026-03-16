// Source: https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a perfect binary tree, reverse the node values at each odd level of the tree.
//
//
// 	For example, suppose the node values at level 3 are [2,1,3,4,7,11,29,18], then it should become [18,29,11,7,4,3,1,2].
//
//
// Return the root of the reversed tree.
//
// A binary tree is perfect if all parent nodes have two children and all leaves are on the same level.
//
// The level of a node is the number of edges along the path between it and the root node.
//
// Example:
// Input: root = [2,3,5,8,13,21,34]
// Output: [2,5,3,8,13,21,34]
// Explanation: 
// The tree has only one odd level.
// The nodes at level 1 are 3, 5 respectively, which are reversed and become 5, 3.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 214].
// 	0 <= Node.val <= 105
// 	root is a perfect binary tree.
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
    TreeNode* reverseOddLevels(TreeNode* root) {
        if (!root) return nullptr;

        queue<TreeNode*> q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int size = q.size();
            vector<TreeNode*> nodes;

            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                nodes.push_back(node);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            if (level % 2 == 1) {
                int left = 0, right = nodes.size() - 1;
                while (left < right) {
                    swap(nodes[left]->val, nodes[right]->val);
                    ++left;
                    --right;
                }
            }

            ++level;
        }

        return root;            
    }
};
