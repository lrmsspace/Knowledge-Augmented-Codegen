// Source: https://leetcode.com/problems/closest-nodes-queries-in-a-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary search tree and an array queries of size n consisting of positive integers.
//
// Find a 2D array answer of size n where answer[i] = [mini, maxi]:
//
//
// 	mini is the largest value in the tree that is smaller than or equal to queries[i]. If a such value does not exist, add -1 instead.
// 	maxi is the smallest value in the tree that is greater than or equal to queries[i]. If a such value does not exist, add -1 instead.
//
//
// Return the array answer.
//
// Example:
// Input: root = [6,2,13,1,4,9,15,null,null,null,null,null,null,14], queries = [2,5,16]
// Output: [[2,2],[4,6],[15,-1]]
// Explanation: We answer the queries in the following way:
// - The largest number that is smaller or equal than 2 in the tree is 2, and the smallest number that is greater or equal than 2 is still 2. So the answer for the first query is [2,2].
// - The largest number that is smaller or equal than 5 in the tree is 4, and the smallest number that is greater or equal than 5 is 6. So the answer for the second query is [4,6].
// - The largest number that is smaller or equal than 16 in the tree is 15, and the smallest number that is greater or equal than 16 does not exist. So the answer for the third query is [15,-1].
//
// Constraints:
// The number of nodes in the tree is in the range [2, 105].
// 	1 <= Node.val <= 106
// 	n == queries.length
// 	1 <= n <= 105
// 	1 <= queries[i] <= 106
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
int** closestNodes(struct TreeNode* root, int* queries, int queriesSize, int* returnSize, int** returnColumnSizes) {
    // Step 1: Inorder Traversal to get sorted values from BST
    int maxNodes = 100000; // As per constraints
    int* sortedValues = (int*)malloc(maxNodes * sizeof(int));
    int count = 0;

    void inorder(struct TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        sortedValues[count++] = node->val;
        inorder(node->right);
    }

    inorder(root);

    // Step 2: Prepare the result array
    int** result = (int**)malloc(queriesSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    // Step 3: For each query, find the closest nodes using binary search
    for (int i = 0; i < queriesSize; i++) {
        int query = queries[i];
        int left = 0, right = count - 1;
        int mini = -1, maxi = -1;

        // Binary search for mini
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (sortedValues[mid] <= query) {
                mini = sortedValues[mid];
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Reset for maxi search
        left = 0;
        right = count - 1;

        // Binary search for maxi
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (sortedValues[mid] >= query) {
                maxi = sortedValues[mid];
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // Store results
        result[i] = (int*)malloc(2 * sizeof(int));
        result[i][0] = mini;
        result[i][1] = maxi;
        (*returnColumnSizes)[i] = 2;
    }

    free(sortedValues);
    return result;      
}
