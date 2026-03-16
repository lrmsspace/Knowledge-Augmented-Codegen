// Source: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.
//
// Example:
// Input: root = [5,3,6,2,4,null,7], k = 9
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-104 <= Node.val <= 104
// 	root is guaranteed to be a valid binary search tree.
// 	-105 <= k <= 105
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
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> seen;
        return dfs(root, k, seen);          
    }
};
