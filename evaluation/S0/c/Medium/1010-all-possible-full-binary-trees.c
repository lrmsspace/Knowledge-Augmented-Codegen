// Source: https://leetcode.com/problems/all-possible-full-binary-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each tree in the answer must have Node.val == 0.
//
// Each element of the answer is the root node of one possible tree. You may return the final list of trees in any order.
//
// A full binary tree is a binary tree where each node has exactly 0 or 2 children.
//
// Example:
// Input: n = 7
// Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
//
// Constraints:
// 1 <= n <= 20
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** allPossibleFBT(int n, int* returnSize) {
    if (n % 2 == 0) {
        *returnSize = 0;
        return NULL;
    }

    struct TreeNode*** dp = (struct TreeNode***)calloc(n + 1, sizeof(struct TreeNode**));
    int* dpSizes = (int*)calloc(n + 1, sizeof(int));

    dp[1] = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    dp[1][0] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    dp[1][0]->val = 0;
    dp[1][0]->left = NULL;
    dp[1][0]->right = NULL;
    dpSizes[1] = 1;

    for (int nodes = 3; nodes <= n; nodes += 2) {
        dp[nodes] = NULL;
        dpSizes[nodes] = 0;

        for (int leftNodes = 1; leftNodes < nodes; leftNodes += 2) {
            int rightNodes = nodes - 1 - leftNodes;

            for (int i = 0; i < dpSizes[leftNodes]; i++) {
                for (int j = 0; j < dpSizes[rightNodes]; j++) {
                    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                    root->val = 0;
                    root->left = dp[leftNodes][i];
                    root->right = dp[rightNodes][j];

                    dp[nodes] = (struct TreeNode**)realloc(dp[nodes], (dpSizes[nodes] + 1) * sizeof(struct TreeNode*));
                    dp[nodes][dpSizes[nodes]] = root;
                    dpSizes[nodes]++;
                }
            }
        }
    }

    *returnSize = dpSizes[n];
    struct TreeNode** result = dp[n];

    for (int i = 1; i <= n; i++) {
        if (i != n) {
            for (int j = 0; j < dpSizes[i]; j++) {
                free(dp[i][j]);
            }
            free(dp[i]);
        }
    }
    free(dpSizes);
    free(dp);

    return result;      
}
