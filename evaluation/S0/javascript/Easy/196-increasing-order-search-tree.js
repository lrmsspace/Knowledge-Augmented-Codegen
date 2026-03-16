// Source: https://leetcode.com/problems/increasing-order-search-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary search tree, rearrange the tree in in-order so that the leftmost node in the tree is now the root of the tree, and every node has no left child and only one right child.
//
// Example:
// Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
// Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
//
// Constraints:
// The number of nodes in the given tree will be in the range [1, 100].
// 	0 <= Node.val <= 1000
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
 * @return {TreeNode}
 */
var increasingBST = function(root) {
    const values = [];

    const inOrderTraversal = (node) => {
        if (!node) return;
        inOrderTraversal(node.left);
        values.push(node.val);
        inOrderTraversal(node.right);
    };
    inOrderTraversal(root);

    const dummy = new TreeNode(0);
    let current = dummy;
    for (const val of values) {
        current.right = new TreeNode(val);
        current = current.right;
    }
    return dummy.right;
};