// Source: https://leetcode.com/problems/binary-tree-level-order-traversal-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values. (i.e., from left to right, level by level from leaf to root).
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: [[15,7],[9,20],[3]]
//
// Constraints:
// The number of nodes in the tree is in the range [0, 2000].
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
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (!root) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    struct TreeNode** queue = malloc(2000 * sizeof(struct TreeNode*));
    int front = 0, rear = 0;

    int** result = malloc(2000 * sizeof(int*));
    *returnColumnSizes = malloc(2000 * sizeof(int));
    *returnSize = 0;

    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;
        int* levelValues = malloc(levelSize * sizeof(int));
        (*returnColumnSizes)[*returnSize] = levelSize;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            levelValues[i] = node->val;

            if (node->left) {
                queue[rear++] = node->left;
            }
            if (node->right) {
                queue[rear++] = node->right;
            }
        }

        result[(*returnSize)++] = levelValues;
    }

    // Reverse the result for bottom-up order
    for (int i = 0; i < *returnSize / 2; i++) {
        int* tempValues = result[i];
        result[i] = result[*returnSize - 1 - i];
        result[*returnSize - 1 - i] = tempValues;

        int tempSize = (*returnColumnSizes)[i];
        (*returnColumnSizes)[i] = (*returnColumnSizes)[*returnSize - 1 - i];
        (*returnColumnSizes)[*returnSize - 1 - i] = tempSize;
    }

    free(queue);
    return result;      
}
