// Source: https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, find the maximum value v for which there exist different nodes a and b where v = |a.val - b.val| and a is an ancestor of b.
//
// A node a is an ancestor of b if either: any child of a is equal to b or any child of a is an ancestor of b.
//
// Example:
// Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
// Output: 7
// Explanation: We have various ancestor-node differences, some of which are given below :
// |8 - 3| = 5
// |3 - 7| = 4
// |8 - 1| = 7
// |10 - 13| = 3
// Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.
//
// Constraints:
// The number of nodes in the tree is in the range [2, 5000].
// 	0 <= Node.val <= 105
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxAncestorDiff(struct TreeNode* root) {
    int maxDiff = 0;

    void dfs(struct TreeNode* node, int curMin, int curMax) {
        if (!node) return;

        if (node->val < curMin) curMin = node->val;
        if (node->val > curMax) curMax = node->val;

        int diff = curMax - curMin;
        if (diff > maxDiff) maxDiff = diff;

        dfs(node->left, curMin, curMax);
        dfs(node->right, curMin, curMax);
    }

    dfs(root, root->val, root->val);
    return maxDiff;     
}
