// Source: https://leetcode.com/problems/add-one-row-to-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree and two integers val and depth, add a row of nodes with value val at the given depth depth.
//
// Note that the root node is at depth 1.
//
// The adding rule is:
//
//
// 	Given the integer depth, for each not null tree node cur at the depth depth - 1, create two tree nodes with value val as cur's left subtree root and right subtree root.
// 	cur's original left subtree should be the left subtree of the new left subtree root.
// 	cur's original right subtree should be the right subtree of the new right subtree root.
// 	If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val as the new root of the whole original tree, and the original tree is the new root's left subtree.
//
// Example:
// Input: root = [4,2,6,3,1,5], val = 1, depth = 2
// Output: [4,1,1,2,null,null,6,3,1,5]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	The depth of the tree is in the range [1, 104].
// 	-100 <= Node.val <= 100
// 	-105 <= val <= 105
// 	1 <= depth <= the depth of tree + 1
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
 * @param {number} val
 * @param {number} depth
 * @return {TreeNode}
 */
var addOneRow = function(root, val, depth) {
    if (depth === 1) {
        return new TreeNode(val, root, null);
    }
    const addRow = (node, currentDepth) => {
        if (!node) return;
        if (currentDepth === depth - 1) {
            const newLeft = new TreeNode(val, node.left, null);
            const newRight = new TreeNode(val, null, node.right);
            node.left = newLeft;
            node.right = newRight;
        } else {
            addRow(node.left, currentDepth + 1);
            addRow(node.right, currentDepth + 1);
        }
    };
    addRow(root, 1);
    return root;
};