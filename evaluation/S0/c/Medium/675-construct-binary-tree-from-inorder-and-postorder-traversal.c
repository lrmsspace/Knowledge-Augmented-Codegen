// Source: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.
//
// Example:
// Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
// Output: [3,9,20,null,null,15,7]
//
// Constraints:
// 1 <= inorder.length <= 3000
// 	postorder.length == inorder.length
// 	-3000 <= inorder[i], postorder[i] <= 3000
// 	inorder and postorder consist of unique values.
// 	Each value of postorder also appears in inorder.
// 	inorder is guaranteed to be the inorder traversal of the tree.
// 	postorder is guaranteed to be the postorder traversal of the tree.
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    if (inorderSize == 0 || postorderSize == 0) {
        return NULL;
    }

    int rootValue = postorder[postorderSize - 1];
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = rootValue;
    root->left = NULL;
    root->right = NULL;

    int rootIndexInInorder = 0;
    for (int i = 0; i < inorderSize; i++) {
        if (inorder[i] == rootValue) {
            rootIndexInInorder = i;
            break;
        }
    }

    int leftSubtreeSize = rootIndexInInorder;
    int rightSubtreeSize = inorderSize - rootIndexInInorder - 1;

    root->left = buildTree(inorder, leftSubtreeSize, postorder, leftSubtreeSize);
    root->right = buildTree(inorder + rootIndexInInorder + 1, rightSubtreeSize,
                            postorder + leftSubtreeSize, rightSubtreeSize);

    return root;        
}
