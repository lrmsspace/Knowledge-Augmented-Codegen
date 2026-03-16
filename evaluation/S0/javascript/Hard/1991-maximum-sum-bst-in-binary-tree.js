// Source: https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given a binary tree root, return the maximum sum of all keys of any sub-tree which is also a Binary Search Tree (BST).
//
// Assume a BST is defined as follows:
//
//
// 	The left subtree of a node contains only nodes with keys less than the node's key.
// 	The right subtree of a node contains only nodes with keys greater than the node's key.
// 	Both the left and right subtrees must also be binary search trees.
//
// Example:
// Input: root = [1,4,3,2,4,2,5,null,null,null,null,null,null,4,6]
// Output: 20
// Explanation: Maximum sum in a valid Binary search tree is obtained in root node with key equal to 3.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 4 * 104].
// 	-4 * 104 <= Node.val <= 4 * 104
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
var maxSumBST = function(root) {
    let maxSum = 0;
    const postOrder = (node) => {
        if (!node) {
            return { isBST: true, min: Infinity, max: -Infinity, sum: 0 };
        }
        const left = postOrder(node.left);
        const right = postOrder(node.right);
        if (left.isBST && right.isBST && node.val > left.max && node.val < right.min) {
            const sum = left.sum + right.sum + node.val;
            maxSum = Math.max(maxSum, sum);
            return {
                isBST: true,
                min: Math.min(left.min, node.val),
                max: Math.max(right.max, node.val),
                sum: sum
            };
        } else {
            return { isBST: false };
        }
    };
    postOrder(root);
    return maxSum;
};