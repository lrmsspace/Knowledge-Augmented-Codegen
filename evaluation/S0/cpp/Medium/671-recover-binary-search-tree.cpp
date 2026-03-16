// Source: https://leetcode.com/problems/recover-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.
//
// Example:
// Input: root = [1,3,null,null,2]
// Output: [3,1,null,null,2]
// Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.
//
// Constraints:
// The number of nodes in the tree is in the range [2, 1000].
// 	-231 <= Node.val <= 231 - 1
//
//
//  
// Follow up: A solution using O(n) space is pretty straight-forward. Could you devise a constant O(1) space solution?
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
    void recoverTree(TreeNode* root) {
        TreeNode *first = nullptr, *second = nullptr, *prev = nullptr;
        TreeNode *current = root;

        while (current) {
            if (!current->left) {
                // Visit current node
                if (prev && prev->val > current->val) {
                    if (!first) first = prev;
                    second = current;
                }
                prev = current;
                current = current->right;
            } else {
                // Find the inorder predecessor of current
                TreeNode* pred = current->left;
                while (pred->right && pred->right != current) {
                    pred = pred->right;
                }

                if (!pred->right) {
                    // Make current as the right child of its inorder predecessor
                    pred->right = current;
                    current = current->left;
                } else {
                    // Revert the changes made in the 'if' part to restore the original tree
                    pred->right = nullptr;

                    // Visit current node
                    if (prev && prev->val > current->val) {
                        if (!first) first = prev;
                        second = current;
                    }
                    prev = current;
                    current = current->right;
                }
            }
        }

        // Swap the values of the two nodes
        if (first && second) {
            std::swap(first->val, second->val);
        }           
    }
};
