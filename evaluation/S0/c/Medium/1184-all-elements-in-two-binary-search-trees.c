// Source: https://leetcode.com/problems/all-elements-in-two-binary-search-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given two binary search trees root1 and root2, return a list containing all the integers from both trees sorted in ascending order.
//
// Example:
// Input: root1 = [2,1,4], root2 = [1,0,3]
// Output: [0,1,1,2,3,4]
//
// Constraints:
// The number of nodes in each tree is in the range [0, 5000].
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
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getAllElements(struct TreeNode* root1, struct TreeNode* root2, int* returnSize) {
    int capacity = 10000;
    int* result = (int*)malloc(capacity * sizeof(int));
    *returnSize = 0;

    // Helper function for in-order traversal
    void inorder(struct TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        if (*returnSize >= capacity) {
            capacity *= 2;
            result = (int*)realloc(result, capacity * sizeof(int));
        }
        result[(*returnSize)++] = node->val;
        inorder(node->right);
    }

    // Perform in-order traversal on both trees
    inorder(root1);
    inorder(root2);

    // Sort the combined results
    qsort(result, *returnSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    return result;      
}
