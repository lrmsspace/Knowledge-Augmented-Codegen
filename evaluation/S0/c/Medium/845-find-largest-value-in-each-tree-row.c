// Source: https://leetcode.com/problems/find-largest-value-in-each-tree-row/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return an array of the largest value in each row of the tree (0-indexed).
//
// Example:
// Input: root = [1,3,2,5,3,null,9]
// Output: [1,3,9]
//
// Constraints:
// The number of nodes in the tree will be in the range [0, 104].
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* largestValues(struct TreeNode* root, int* returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }

    int capacity = 100;
    int* result = (int*)malloc(capacity * sizeof(int));
    int size = 0;

    struct TreeNode** queue = (struct TreeNode**)malloc(10000 * sizeof(struct TreeNode*));
    int front = 0, back = 0;
    queue[back++] = root;

    while (front < back) {
        int levelSize = back - front;
        int maxVal = queue[front]->val;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            if (node->val > maxVal) {
                maxVal = node->val;
            }
            if (node->left) {
                queue[back++] = node->left;
            }
            if (node->right) {
                queue[back++] = node->right;
            }
        }

        if (size >= capacity) {
            capacity *= 2;
            result = (int*)realloc(result, capacity * sizeof(int));
        }
        result[size++] = maxVal;
    }

    free(queue);
    *returnSize = size;
    return result;      
}
