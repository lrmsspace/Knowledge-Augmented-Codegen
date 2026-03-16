// Source: https://leetcode.com/problems/recover-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.
//
// Example:
// Input: root = [1,3,null,null,2]
// Output: [3,1,null,null,2]
// Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.
//
// Constraints:
// The number of nodes in the tree is in the range [2, 1000].
// 	-231 <= Node.val <= 231 - 1
//
//
//  
// Follow up: A solution using O(n) space is pretty straight-forward. Could you devise a constant O(1) space solution?
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void recoverTree(struct TreeNode* root) {
    struct TreeNode *first = NULL, *second = NULL, *prev = NULL;
    struct TreeNode *current = root, *predecessor = NULL;

    while (current != NULL) {
        if (current->left == NULL) {
            // Visit current node
            if (prev != NULL && prev->val > current->val) {
                if (first == NULL) {
                    first = prev;
                }
                second = current;
            }
            prev = current;
            current = current->right;
        } else {
            // Find the inorder predecessor of current
            predecessor = current->left;
            while (predecessor->right != NULL && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            // Make current as the right child of its inorder predecessor
            if (predecessor->right == NULL) {
                predecessor->right = current;
                current = current->left;
            } else {
                // Revert the changes made in the 'if' part to restore the original tree
                predecessor->right = NULL;

                // Visit current node
                if (prev != NULL && prev->val > current->val) {
                    if (first == NULL) {
                        first = prev;
                    }
                    second = current;
                }
                prev = current;
                current = current->right;
            }
        }
    }

    // Swap the values of the two nodes to correct the BST
    if (first != NULL && second != NULL) {
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }       
}
