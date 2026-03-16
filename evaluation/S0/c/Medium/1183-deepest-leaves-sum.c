// Source: https://leetcode.com/problems/deepest-leaves-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the sum of values of its deepest leaves.
//
// Example:
// Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
// Output: 15
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	1 <= Node.val <= 100
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int deepestLeavesSum(struct TreeNode* root) {
    if (!root) return 0;

    int sum = 0;
    struct TreeNode** queue = malloc(10000 * sizeof(struct TreeNode*));
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;
        sum = 0;

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
    }

    free(queue);
    return sum;     
}
