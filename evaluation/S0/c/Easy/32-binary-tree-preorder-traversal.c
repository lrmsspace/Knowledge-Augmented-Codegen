// Source: https://leetcode.com/problems/binary-tree-preorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return the preorder traversal of its nodes' values.
//
// Example:
// Input: root = [1,null,2,3]
//
// Output: [1,2,3]
//
// Explanation:
//
// Constraints:
// The number of nodes in the tree is in the range [0, 100].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow up: Recursive solution is trivial, could you do it iteratively?
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
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = (int*)malloc(100 * sizeof(int));
    *returnSize = 0;
    if (!root) {
        return result;
    }

    struct TreeNode** stack = (struct TreeNode**)malloc(100 * sizeof(struct TreeNode*));
    int stackSize = 0;

    stack[stackSize++] = root;

    while (stackSize > 0) {
        struct TreeNode* node = stack[--stackSize];
        result[(*returnSize)++] = node->val;

        if (node->right) {
            stack[stackSize++] = node->right;
        }
        if (node->left) {
            stack[stackSize++] = node->left;
        }
    }

    free(stack);
    return result;      
}
