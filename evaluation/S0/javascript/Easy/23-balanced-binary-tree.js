// Source: https://leetcode.com/problems/balanced-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary tree, determine if it is height-balanced.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [0, 5000].
// 	-104 <= Node.val <= 104
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
var isBalanced = function(root) {
    const checkBalance = (node) => {
        if (!node) return 0;
        const leftHeight = checkBalance(node.left);
        if (leftHeight === -1) return -1;
        const rightHeight = checkBalance(node.right);
        if (rightHeight === -1) return -1;
        if (Math.abs(leftHeight - rightHeight) > 1) return -1;
        return Math.max(leftHeight, rightHeight) + 1;
    };
    return checkBalance(root) !== -1;
};
