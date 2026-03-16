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

    const inorder = (node) => {
        if (!node) return;
        inorder(node.left);
        if (prev !== null) {
            minDiff = Math.min(minDiff, node.val - prev);
        }
        prev = node.val;
        inorder(node.right);
    };

    inorder(root);
    return minDiff;
};