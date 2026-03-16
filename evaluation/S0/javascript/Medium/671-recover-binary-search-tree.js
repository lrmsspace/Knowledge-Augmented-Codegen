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
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {void} Do not return anything, modify root in-place instead.
 */
var recoverTree = function(root) {
    let first = null;
    let second = null;
    let prev = new TreeNode(-Infinity);

    const inorder = (node) => {
        if (!node) return;
        inorder(node.left);
        if (prev.val >= node.val) {
            if (!first) first = prev;
            second = node;
        }
        prev = node;
        inorder(node.right);
    };

    inorder(root);
    [first.val, second.val] = [second.val, first.val];
};