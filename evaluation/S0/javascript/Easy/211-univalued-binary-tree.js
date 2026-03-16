// Source: https://leetcode.com/problems/univalued-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// A binary tree is uni-valued if every node in the tree has the same value.
//
// Given the root of a binary tree, return true if the given tree is uni-valued, or false otherwise.
//
// Example:
// Input: root = [1,1,1,1,1,null,1]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 100].
// 	0 <= Node.val < 100
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
var isUnivalTree = function(root) {
    if (root === null) return true;
    const value = root.val;
    function dfs(node) {
        if (node === null) return true;
        if (node.val !== value) return false;
        return dfs(node.left) && dfs(node.right);
    }
    return dfs(root);
};