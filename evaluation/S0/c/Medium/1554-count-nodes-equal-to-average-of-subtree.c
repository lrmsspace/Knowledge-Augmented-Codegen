// Source: https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the number of nodes where the value of the node is equal to the average of the values in its subtree.
//
// Note:
//
//
// 	The average of n elements is the sum of the n elements divided by n and rounded down to the nearest integer.
// 	A subtree of root is a tree consisting of root and all of its descendants.
//
// Example:
// Input: root = [4,8,5,0,1,null,6]
// Output: 5
// Explanation: 
// For the node with value 4: The average of its subtree is (4 + 8 + 5 + 0 + 1 + 6) / 6 = 24 / 6 = 4.
// For the node with value 5: The average of its subtree is (5 + 6) / 2 = 11 / 2 = 5.
// For the node with value 0: The average of its subtree is 0 / 1 = 0.
// For the node with value 1: The average of its subtree is 1 / 1 = 1.
// For the node with value 6: The average of its subtree is 6 / 1 = 6.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	0 <= Node.val <= 1000
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int averageOfSubtree(struct TreeNode* root) {
    int count = 0;

    int dfs(struct TreeNode* node) {
        if (!node) return 0;

        int leftSum = dfs(node->left);
        int rightSum = dfs(node->right);

        int leftCount = node->left ? dfs_count(node->left) : 0;
        int rightCount = node->right ? dfs_count(node->right) : 0;

        int totalSum = leftSum + rightSum + node->val;
        int totalCount = leftCount + rightCount + 1;

        if (node->val == totalSum / totalCount) {
            count++;
        }

        return totalSum;
    }

    int dfs_count(struct TreeNode* node) {
        if (!node) return 0;
        return 1 + dfs_count(node->left) + dfs_count(node->right);
    }

    dfs(root);
    return count;       
}
