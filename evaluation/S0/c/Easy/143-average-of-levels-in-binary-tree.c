// Source: https://leetcode.com/problems/average-of-levels-in-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return the average value of the nodes on each level in the form of an array. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: [3.00000,14.50000,11.00000]
// Explanation: The average value of nodes on level 0 is 3, on level 1 is 14.5, and on level 2 is 11.
// Hence return [3, 14.5, 11].
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }

    // Queue for level order traversal
    struct TreeNode** queue = (struct TreeNode**)malloc(10000 * sizeof(struct TreeNode*));
    int front = 0, rear = 0;

    // Result array
    double* result = (double*)malloc(10000 * sizeof(double));
    int levelCount = 0;

    // Enqueue root
    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;
        long long sum = 0;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            sum += node->val;

            if (node->left) {
                queue[rear++] = node->left;
            }
            if (node->right) {
                queue[rear++] = node->right;
            }
        }

        result[levelCount++] = (double)sum / levelSize;
    }

    free(queue);
    *returnSize = levelCount;
    return result;      
}
