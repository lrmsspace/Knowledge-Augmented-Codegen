// Source: https://leetcode.com/problems/longest-univalue-path/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the length of the longest path, where each node in the path has the same value. This path may or may not pass through the root.
//
// The length of the path between two nodes is represented by the number of edges between them.
//
// Example:
// Input: root = [5,4,5,1,1,null,5]
// Output: 2
// Explanation: The shown image shows that the longest path of the same value (i.e. 5).
//
// Constraints:
// The number of nodes in the tree is in the range [0, 104].
// 	-1000 <= Node.val <= 1000
// 	The depth of the tree will not exceed 1000.
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int longestUnivaluePath(struct TreeNode* root) {
    int maxLen = 0;

    int dfs(struct TreeNode* node) {
        if (!node) return 0;

        int leftLen = dfs(node->left);
        int rightLen = dfs(node->right);

        int leftPath = 0, rightPath = 0;
        if (node->left && node->left->val == node->val) {
            leftPath = leftLen + 1;
        }
        if (node->right && node->right->val == node->val) {
            rightPath = rightLen + 1;
        }

        maxLen = fmax(maxLen, leftPath + rightPath);
        return fmax(leftPath, rightPath);
    }

    dfs(root);
    return maxLen;      
}
