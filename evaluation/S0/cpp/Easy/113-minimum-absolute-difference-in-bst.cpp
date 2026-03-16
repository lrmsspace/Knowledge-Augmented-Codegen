// Source: https://leetcode.com/problems/minimum-absolute-difference-in-bst/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.
//
// Example:
// Input: root = [4,2,6,1,3]
// Output: 1
//
// Constraints:
// The number of nodes in the tree is in the range [2, 104].
// 	0 <= Node.val <= 105
//
//
//  
// Note: This question is the same as 783: https://leetcode.com/problems/minimum-distance-between-bst-nodes/
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
    int getMinimumDifference(TreeNode* root) {
        int minDiff = INT_MAX;
        TreeNode* prev = nullptr;

        inorderTraversal(root, prev, minDiff);

        return minDiff;         
    }
};
