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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

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
 * @return {number}
 */
var minDiffInBST = function(root) {
    let prev = null;
    let minDiff = Infinity; 

    function inorder(node) {
        if (!node) return;
        inorder(node.left);
        if (prev !== null) {
            minDiff = Math.min(minDiff, node.val - prev);
        }
        prev = node.val;
        inorder(node.right);
    }

    inorder(root);
    return minDiff;
};