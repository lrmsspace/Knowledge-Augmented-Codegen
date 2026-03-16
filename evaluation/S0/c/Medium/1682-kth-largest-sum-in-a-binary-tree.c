// Source: https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree and a positive integer k.
//
// The level sum in the tree is the sum of the values of the nodes that are on the same level.
//
// Return the kth largest level sum in the tree (not necessarily distinct). If there are fewer than k levels in the tree, return -1.
//
// Note that two nodes are on the same level if they have the same distance from the root.
//
// Example:
// Input: root = [5,8,9,2,1,3,7,4,6], k = 2
// Output: 13
// Explanation: The level sums are the following:
// - Level 1: 5.
// - Level 2: 8 + 9 = 17.
// - Level 3: 2 + 1 + 3 + 7 = 13.
// - Level 4: 4 + 6 = 10.
// The 2nd largest level sum is 13.
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= 106
// 	1 <= k <= n
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
long long kthLargestLevelSum(struct TreeNode* root, int k) {
    if (!root) return -1;

    // Max heap to store level sums
    long long levelSums[100000];
    int levelCount = 0;

    // Queue for level order traversal
    struct TreeNode* queue[100000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;
        long long levelSum = 0;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            levelSum += node->val;

            if (node->left) {
                queue[rear++] = node->left;
            }
            if (node->right) {
                queue[rear++] = node->right;
            }
        }

        levelSums[levelCount++] = levelSum;
    }

    // Sort level sums in descending order
    for (int i = 0; i < levelCount - 1; i++) {
        for (int j = i + 1; j < levelCount; j++) {
            if (levelSums[i] < levelSums[j]) {
                long long temp = levelSums[i];
                levelSums[i] = levelSums[j];
                levelSums[j] = temp;
            }
        }
    }

    return (k <= levelCount) ? levelSums[k - 1] : -1;       
}
