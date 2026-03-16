// Source: https://leetcode.com/problems/minimum-absolute-difference-in-bst/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.
//
// Example:
// Input: root = [4,2,6,1,3]
// Output: 1
//
// Constraints:
// The number of nodes in the tree is in the range [2, 104].
// 	0 <= Node.val <= 105
//
//
//  
// Note: This question is the same as 783: https://leetcode.com/problems/minimum-distance-between-bst-nodes/
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int getMinimumDifference(struct TreeNode* root) {
    int min_diff = 100000;
    struct TreeNode* stack[10000];
    int top = -1;
    struct TreeNode* curr = root;
    struct TreeNode* prev = NULL;

    while (top != -1 || curr != NULL) {
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        if (prev != NULL) {
            int diff = curr->val - prev->val;
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
        prev = curr;
        curr = curr->right;
    }

    return min_diff;        
}
