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
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {number[]} inorder
 * @param {number[]} postorder
 * @return {TreeNode}
 */
var buildTree = function(inorder, postorder) {
    if (inorder.length === 0 || postorder.length === 0) return null;

    const rootVal = postorder[postorder.length - 1];
    const root = new TreeNode(rootVal);

    const rootIndex = inorder.indexOf(rootVal);

    root.left = buildTree(inorder.slice(0, rootIndex), postorder.slice(0, rootIndex));
    root.right = buildTree(inorder.slice(rootIndex + 1), postorder.slice(rootIndex, postorder.length - 1));

    return root;
};