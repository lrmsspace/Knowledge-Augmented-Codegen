// Source: https://leetcode.com/problems/add-one-row-to-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree and two integers val and depth, add a row of nodes with value val at the given depth depth.
//
// Note that the root node is at depth 1.
//
// The adding rule is:
//
//
// 	Given the integer depth, for each not null tree node cur at the depth depth - 1, create two tree nodes with value val as cur's left subtree root and right subtree root.
// 	cur's original left subtree should be the left subtree of the new left subtree root.
// 	cur's original right subtree should be the right subtree of the new right subtree root.
// 	If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val as the new root of the whole original tree, and the original tree is the new root's left subtree.
//
// Example:
// Input: root = [4,2,6,3,1,5], val = 1, depth = 2
// Output: [4,1,1,2,null,null,6,3,1,5]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	The depth of the tree is in the range [1, 104].
// 	-100 <= Node.val <= 100
// 	-105 <= val <= 105
// 	1 <= depth <= the depth of tree + 1
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* addOneRow(struct TreeNode* root, int val, int depth) {
    if (depth == 1) {
        struct TreeNode* newRoot = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newRoot->val = val;
        newRoot->left = root;
        newRoot->right = NULL;
        return newRoot;
    }

    void dfs(struct TreeNode* node, int currentDepth) {
        if (!node) return;
        if (currentDepth == depth - 1) {
            struct TreeNode* newLeft = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            struct TreeNode* newRight = (struct TreeNode*)malloc(sizeof(struct TreeNode));
            newLeft->val = val;
            newRight->val = val;

            newLeft->left = node->left;
            newLeft->right = NULL;
            newRight->right = node->right;
            newRight->left = NULL;

            node->left = newLeft;
            node->right = newRight;
        } else {
            dfs(node->left, currentDepth + 1);
            dfs(node->right, currentDepth + 1);
        }
    }

    dfs(root, 1);
    return root;        
}
