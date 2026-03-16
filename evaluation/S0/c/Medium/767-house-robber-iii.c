// Source: https://leetcode.com/problems/house-robber-iii/   |   Difficulty: Medium
//
// Problem Description:
// The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.
//
// Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if two directly-linked houses were broken into on the same night.
//
// Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.
//
// Example:
// Input: root = [3,2,3,null,3,null,1]
// Output: 7
// Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	0 <= Node.val <= 104
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int rob(struct TreeNode* root) {
    int rob_helper(struct TreeNode* node, int* robbed, int* not_robbed) {
        if (!node) {
            *robbed = 0;
            *not_robbed = 0;
            return 0;
        }

        int left_robbed = 0, left_not_robbed = 0;
        int right_robbed = 0, right_not_robbed = 0;

        rob_helper(node->left, &left_robbed, &left_not_robbed);
        rob_helper(node->right, &right_robbed, &right_not_robbed);

        *robbed = node->val + left_not_robbed + right_not_robbed;
        *not_robbed = (left_robbed > left_not_robbed ? left_robbed : left_not_robbed) +
                      (right_robbed > right_not_robbed ? right_robbed : right_not_robbed);

        return 0;
    }

    int robbed = 0, not_robbed = 0;
    rob_helper(root, &robbed, &not_robbed);
    return (robbed > not_robbed) ? robbed : not_robbed;     
}
