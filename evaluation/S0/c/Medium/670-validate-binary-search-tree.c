// Source: https://leetcode.com/problems/validate-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, determine if it is a valid binary search tree (BST).
//
// A valid BST is defined as follows:
//
//
// 	The left subtree of a node contains only nodes with keys strictly less than the node's key.
// 	The right subtree of a node contains only nodes with keys strictly greater than the node's key.
// 	Both the left and right subtrees must also be binary search trees.
//
// Example:
// Input: root = [2,1,3]
// Output: true
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
bool isValidBST(struct TreeNode* root) {
    long long min = (long long)INT_MIN - 1;
    long long max = (long long)INT_MAX + 1;

    struct TreeNode** stack = (struct TreeNode**)malloc(10000 * sizeof(struct TreeNode*));
    long long* minStack = (long long*)malloc(10000 * sizeof(long long));
    long long* maxStack = (long long*)malloc(10000 * sizeof(long long));
    int top = -1;

    stack[++top] = root;
    minStack[top] = min;
    maxStack[top] = max;

    while (top >= 0) {
        struct TreeNode* node = stack[top];
        long long currMin = minStack[top];
        long long currMax = maxStack[top];
        top--;

        if (node->val <= currMin || node->val >= currMax) {
            free(stack);
            free(minStack);
            free(maxStack);
            return false;
        }

        if (node->right) {
            stack[++top] = node->right;
            minStack[top] = node->val;
            maxStack[top] = currMax;
        }

        if (node->left) {
            stack[++top] = node->left;
            minStack[top] = currMin;
            maxStack[top] = node->val;
        }
    }

    free(stack);
    free(minStack);
    free(maxStack);
    return true;        
}
