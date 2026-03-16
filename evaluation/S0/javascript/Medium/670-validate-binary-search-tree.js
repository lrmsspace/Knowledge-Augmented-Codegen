// Source: https://leetcode.com/problems/validate-binary-search-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, determine if it is a valid binary search tree (BST).
//
// A valid BST is defined as follows:
//
//
// 	The left subtree of a node contains only nodes with keys strictly less than the node's key.
// 	The right subtree of a node contains only nodes with keys strictly greater than the node's key.
// 	Both the left and right subtrees must also be binary search trees.
//
// Example:
// Input: root = [2,1,3]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-231 <= Node.val <= 231 - 1
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
 * @return {boolean}
 */
var isValidBST = function(root) {
    const validate = (node, low, high) => {
        if (!node) return true;
        if (node.val <= low || node.val >= high) return false;
        return validate(node.left, low, node.val) && validate(node.right, node.val, high);
    };

    return validate(root, -Infinity, Infinity);
};
