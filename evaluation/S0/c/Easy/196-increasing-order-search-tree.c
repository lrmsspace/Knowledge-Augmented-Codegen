// Source: https://leetcode.com/problems/increasing-order-search-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only one right child.
//
// Example:
// Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
// Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
//
// Constraints:
// The number of nodes in the given tree will be in the range [1, 100].
// 	0 <= Node.val <= 1000
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* increasingBST(struct TreeNode* root) {
    struct TreeNode dummy;
    struct TreeNode* current = &dummy;
    struct TreeNode* stack[100];
    int top = -1;
    struct TreeNode* node = root;

    while (top != -1 || node != NULL) {
        while (node != NULL) {
            stack[++top] = node;
            node = node->left;
        }
        node = stack[top--];
        current->right = node;
        node->left = NULL;
        current = node;
        node = node->right;
    }

    return dummy.right;     
}
