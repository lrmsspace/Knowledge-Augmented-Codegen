// Source: https://leetcode.com/problems/minimum-distance-between-bst-nodes/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a Binary Search Tree (BST), return the minimum difference between the values of any two different nodes in the tree.
//
// Example:
// Input: root = [4,2,6,1,3]
// Output: 1
//
// Constraints:
// The number of nodes in the tree is in the range [2, 100].
// 	0 <= Node.val <= 105
//
//
//  
// Note: This question is the same as 530: https://leetcode.com/problems/minimum-absolute-difference-in-bst/
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minDiffInBST(struct TreeNode* root) {
    int min_diff = 100001;
    struct TreeNode* prev = NULL;
    struct TreeNode* stack[100];
    int stack_size = 0;
    struct TreeNode* current = root;

    while (stack_size > 0 || current != NULL) {
        while (current != NULL) {
            stack[stack_size++] = current;
            current = current->left;
        }
        current = stack[--stack_size];
        if (prev != NULL) {
            int diff = current->val - prev->val;
            if (diff < min_diff) {
                min_diff = diff;
            }
        }
        prev = current;
        current = current->right;
    }

    return min_diff;        
}
