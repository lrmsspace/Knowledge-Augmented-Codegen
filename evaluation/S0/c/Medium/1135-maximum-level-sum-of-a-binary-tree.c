// Source: https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.
//
// Return the smallest level x such that the sum of all the values of nodes at level x is maximal.
//
// Example:
// Input: root = [1,7,0,7,-8,null,null]
// Output: 2
// Explanation: 
// Level 1 sum = 1.
// Level 2 sum = 7 + 0 = 7.
// Level 3 sum = 7 + -8 = -1.
// So we return the level with the maximum sum which is level 2.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-105 <= Node.val <= 105
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxLevelSum(struct TreeNode* root) {
    if (!root) return 0;

    int maxSum = root->val;
    int resultLevel = 1;
    int currentLevel = 1;

    struct TreeNode** queue = malloc(10000 * sizeof(struct TreeNode*));
    int front = 0, back = 0;

    queue[back++] = root;

    while (front < back) {
        int levelSize = back - front;
        int currentSum = 0;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            currentSum += node->val;

            if (node->left) {
                queue[back++] = node->left;
            }
            if (node->right) {
                queue[back++] = node->right;
            }
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            resultLevel = currentLevel;
        }

        currentLevel++;
    }

    free(queue);
    return resultLevel;     
}
