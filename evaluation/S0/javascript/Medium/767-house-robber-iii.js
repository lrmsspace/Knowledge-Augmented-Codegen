// Source: https://leetcode.com/problems/house-robber-iii/   |   Difficulty: Medium
//
// Problem Description:
// The thief has found himself a new place for his thievery again. There is only one entrance to this area, called root.
//
// Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if two directly-linked houses were broken into on the same night.
//
// Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.
//
// Example:
// Input: root = [3,2,3,null,3,null,1]
// Output: 7
// Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	0 <= Node.val <= 104
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
 * @return {number}
 */
var rob = function(root) {
    const memo = new Map();

    const helper = (node) => {
        if (!node) return 0;
        if (memo.has(node)) return memo.get(node);

        const robCurrent = node.val + (node.left ? helper(node.left.left) + helper(node.left.right) : 0) + (node.right ? helper(node.right.left) + helper(node.right.right) : 0);
        const skipCurrent = helper(node.left) + helper(node.right);

        const result = Math.max(robCurrent, skipCurrent);
        memo.set(node, result);
        return result;
    };

    return helper(root);
};