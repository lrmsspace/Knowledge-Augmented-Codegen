// Source: https://leetcode.com/problems/binary-tree-postorder-traversal/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, return the postorder traversal of its nodes' values.
//
// Example:
// Input: root = [1,null,2,3]
//
// Output: [3,2,1]
//
// Explanation:
//
// Constraints:
// The number of the nodes in the tree is in the range [0, 100].
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
int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = NULL;
    *returnSize = 0;
    if (!root) return result;

    struct TreeNode** stack = (struct TreeNode**)malloc(100 * sizeof(struct TreeNode*));
    int top = -1;
    struct TreeNode* current = root;
    struct TreeNode* lastVisited = NULL;

    while (top != -1 || current) {
        while (current) {
            stack[++top] = current;
            current = current->left;
        }
        struct TreeNode* peekNode = stack[top];
        if (peekNode->right && lastVisited != peekNode->right) {
            current = peekNode->right;
        } else {
            result = (int*)realloc(result, (*returnSize + 1) * sizeof(int));
            result[(*returnSize)++] = peekNode->val;
            lastVisited = stack[top--];
        }
    }

    free(stack);
    return result;      
}
