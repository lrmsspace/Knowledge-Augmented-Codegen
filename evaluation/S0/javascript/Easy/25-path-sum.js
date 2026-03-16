// Source: https://leetcode.com/problems/path-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.
//
// A leaf is a node with no children.
//
// Example:
// Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
// Output: true
// Explanation: The root-to-leaf path with the target sum is shown.
//
// Constraints:
// The number of nodes in the tree is in the range [0, 5000].
// 	-1000 <= Node.val <= 1000
// 	-1000 <= targetSum <= 1000
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
 * @param {number} targetSum
 * @return {boolean}
 */
var hasPathSum = function(root, targetSum) {
    if (!root) return false;
    if (!root.left && !root.right) {
        return root.val === targetSum;
    }
    const newTarget = targetSum - root.val;
    return hasPathSum(root.left, newTarget) || hasPathSum(root.right, newTarget);
};
