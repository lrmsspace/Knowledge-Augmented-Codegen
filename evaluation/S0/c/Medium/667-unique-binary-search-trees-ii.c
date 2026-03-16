// Source: https://leetcode.com/problems/unique-binary-search-trees-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.
//
// Example:
// Input: n = 3
// Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
//
// Constraints:
// 1 <= n <= 8
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
struct TreeNode** generateTrees(int n, int* returnSize) {
    if (n == 0) {
        *returnSize = 0;
        return NULL;
    }

    struct TreeNode*** dp = (struct TreeNode***)malloc((n + 1) * sizeof(struct TreeNode**));
    int* dpSizes = (int*)malloc((n + 1) * sizeof(int));
    dp[0] = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    dp[0][0] = NULL;
    dpSizes[0] = 1;

    for (int len = 1; len <= n; len++) {
        dp[len] = NULL;
        dpSizes[len] = 0;

        for (int root = 1; root <= len; root++) {
            int leftSize = dpSizes[root - 1];
            int rightSize = dpSizes[len - root];

            for (int i = 0; i < leftSize; i++) {
                for (int j = 0; j < rightSize; j++) {
                    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                    newNode->val = root;

                    newNode->left = dp[root - 1][i];

                    struct TreeNode* rightSubtree = dp[len - root][j];
                    if (rightSubtree != NULL) {
                        struct TreeNode* clonedRight = cloneTree(rightSubtree, root);
                        newNode->right = clonedRight;
                    } else {
                        newNode->right = NULL;
                    }

                    dp[len] = (struct TreeNode**)realloc(dp[len], (dpSizes[len] + 1) * sizeof(struct TreeNode*));
                    dp[len][dpSizes[len]] = newNode;
                    dpSizes[len]++;
                }
            }
        }
    }

    *returnSize = dpSizes[n];
    struct TreeNode** result = dp[n];

    for (int i = 0; i <= n; i++) {
        if (i != n) {
            free(dp[i]);
        }
    }
    free(dp);
    free(dpSizes);

    return result;      
}
