// Source: https://leetcode.com/problems/count-complete-tree-nodes/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a complete binary tree, return the number of the nodes in the tree.
//
// According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
//
// Design an algorithm that runs in less than O(n) time complexity.
//
// Example:
// Input: root = [1,2,3,4,5,6]
// Output: 6
//
// Constraints:
// The number of nodes in the tree is in the range [0, 5 * 104].
// 	0 <= Node.val <= 5 * 104
// 	The tree is guaranteed to be complete.
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
var countNodes = function(root) {
    if (root === null) {
        return 0;
    }
    let leftDepth = 0;
    let rightDepth = 0;
    let leftNode = root;
    let rightNode = root;
    while (leftNode !== null) {
        leftDepth++;
        leftNode = leftNode.left;
    }
    while (rightNode !== null) {
        rightDepth++;
        rightNode = rightNode.right;
    }
    if (leftDepth === rightDepth) {
        return Math.pow(2, leftDepth) - 1;
    }
    return 1 + countNodes(root.left) + countNodes(root.right);
};