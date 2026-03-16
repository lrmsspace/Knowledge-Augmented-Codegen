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
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int findBottomLeftValue(struct TreeNode* root) {
    int bottomLeftValue = 0;
    int maxDepth = -1;

    void dfs(struct TreeNode* node, int depth) {
        if (!node) return;

        // If this is the first time we reach this depth, update bottomLeftValue
        if (depth > maxDepth) {
            maxDepth = depth;
            bottomLeftValue = node->val;
        }

        // Traverse left subtree first to ensure leftmost value is found first
        dfs(node->left, depth + 1);
        dfs(node->right, depth + 1);
    }

    dfs(root, 0);
    return bottomLeftValue;     
}
