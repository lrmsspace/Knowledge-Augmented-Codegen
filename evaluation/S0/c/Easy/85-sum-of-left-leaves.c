// Source: https://leetcode.com/problems/sum-of-left-leaves/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return the sum of all left leaves.
//
// A leaf is a node with no children. A left leaf is a leaf that is the left child of another node.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: 24
// Explanation: There are two left leaves in the binary tree, with values 9 and 15 respectively.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	-1000 <= Node.val <= 1000
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int sumOfLeftLeaves(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int sum = 0;

    if (root->left != NULL) {
        // Check if the left child is a leaf
        if (root->left->left == NULL && root->left->right == NULL) {
            sum += root->left->val; // Add left leaf value to sum
        } else {
            sum += sumOfLeftLeaves(root->left); // Recur on left subtree
        }
    }

    sum += sumOfLeftLeaves(root->right); // Recur on right subtree

    return sum;     
}
