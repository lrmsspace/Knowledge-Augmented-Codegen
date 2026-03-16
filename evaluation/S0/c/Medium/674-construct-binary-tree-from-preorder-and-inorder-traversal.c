// Source: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.
//
// Example:
// Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// Output: [3,9,20,null,null,15,7]
//
// Constraints:
// 1 <= preorder.length <= 3000
// 	inorder.length == preorder.length
// 	-3000 <= preorder[i], inorder[i] <= 3000
// 	preorder and inorder consist of unique values.
// 	Each value of inorder also appears in preorder.
// 	preorder is guaranteed to be the preorder traversal of the tree.
// 	inorder is guaranteed to be the inorder traversal of the tree.
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    if (preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    root->left = NULL;
    root->right = NULL;

    int rootIndexInInorder = 0;
    for (int i = 0; i < inorderSize; i++) {
        if (inorder[i] == root->val) {
            rootIndexInInorder = i;
            break;
        }
    }

    int leftSubtreeSize = rootIndexInInorder;
    int rightSubtreeSize = inorderSize - rootIndexInInorder - 1;

    root->left = buildTree(preorder + 1, leftSubtreeSize, inorder, leftSubtreeSize);
    root->right = buildTree(preorder + 1 + leftSubtreeSize, rightSubtreeSize, inorder + rootIndexInInorder + 1, rightSubtreeSize);

    return root;        
}
