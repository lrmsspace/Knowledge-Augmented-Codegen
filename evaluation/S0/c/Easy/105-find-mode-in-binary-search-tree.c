// Source: https://leetcode.com/problems/find-mode-in-binary-search-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary search tree (BST) with duplicates, return all the mode(s) (i.e., the most frequently occurred element) in it.
//
// If the tree has more than one mode, return them in any order.
//
// Assume a BST is defined as follows:
//
//
// 	The left subtree of a node contains only nodes with keys less than or equal to the node's key.
// 	The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
// 	Both the left and right subtrees must also be binary search trees.
//
// Example:
// Input: root = [1,null,2,2]
// Output: [2]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-105 <= Node.val <= 105
//
//
//  
// Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
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
int* findMode(struct TreeNode* root, int* returnSize) {
    int maxCount = 0;
    int currentCount = 0;
    int currentValue = 0;
    int modesCapacity = 10;
    int* modes = malloc(modesCapacity * sizeof(int));
    *returnSize = 0;

    void inOrder(struct TreeNode* node) {
        if (!node) return;

        inOrder(node->left);

        if (node->val == currentValue) {
            currentCount++;
        } else {
            currentValue = node->val;
            currentCount = 1;
        }

        if (currentCount > maxCount) {
            maxCount = currentCount;
            *returnSize = 0;
            modes[(*returnSize)++] = currentValue;
        } else if (currentCount == maxCount) {
            if (*returnSize >= modesCapacity) {
                modesCapacity *= 2;
                modes = realloc(modes, modesCapacity * sizeof(int));
            }
            modes[(*returnSize)++] = currentValue;
        }

        inOrder(node->right);
    }

    inOrder(root);
    return modes;       
}
