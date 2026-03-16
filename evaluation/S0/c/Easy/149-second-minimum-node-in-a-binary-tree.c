// Source: https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes. More formally, the property root.val = min(root.left.val, root.right.val) always holds.
//
// Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.
//
// If no such second minimum value exists, output -1 instead.
//
// Example:
// Input: root = [2,2,5,null,null,5,7]
// Output: 5
// Explanation: The smallest value is 2, the second smallest value is 5.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 25].
// 	1 <= Node.val <= 231 - 1
// 	root.val == min(root.left.val, root.right.val) for each internal node of the tree.
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int findSecondMinimumValue(struct TreeNode* root) {
    long long first_min = root->val;
    long long second_min = 9223372036854775807; // LLONG_MAX

    void dfs(struct TreeNode* node) {
        if (!node) return;

        if (node->val > first_min && node->val < second_min) {
            second_min = node->val;
        }

        dfs(node->left);
        dfs(node->right);
    }

    dfs(root);

    return (second_min == 9223372036854775807) ? -1 : (int)second_min;      
}
