// Source: https://leetcode.com/problems/delete-nodes-and-return-forest/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, each node in the tree has a distinct value.
//
// After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).
//
// Return the roots of the trees in the remaining forest. You may return the result in any order.
//
// Example:
// Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
// Output: [[1,2,null,4],[6],[7]]
//
// Constraints:
// The number of nodes in the given tree is at most 1000.
// 	Each node has a distinct value between 1 and 1000.
// 	to_delete.length <= 1000
// 	to_delete contains distinct values between 1 and 1000.
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
struct TreeNode** delNodes(struct TreeNode* root, int* to_delete, int to_deleteSize, int* returnSize){
    int del_map[1001] = {0};
    for (int i = 0; i < to_deleteSize; i++) {
        del_map[to_delete[i]] = 1;
    }

    struct TreeNode** result = (struct TreeNode**)malloc(1000 * sizeof(struct TreeNode*));
    *returnSize = 0;

    struct TreeNode* helper(struct TreeNode* node, int is_root) {
        if (!node) {
            return NULL;
        }

        int deleted = del_map[node->val];
        if (is_root && !deleted) {
            result[(*returnSize)++] = node;
        }

        node->left = helper(node->left, deleted);
        node->right = helper(node->right, deleted);

        return deleted ? NULL : node;
    }

    helper(root, 1);
    return result;
}
