// Source: https://leetcode.com/problems/cousins-in-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree with unique values and the values of two different nodes of the tree x and y, return true if the nodes corresponding to the values x and y in the tree are cousins, or false otherwise.
//
// Two nodes of a binary tree are cousins if they have the same depth with different parents.
//
// Note that in a binary tree, the root node is at the depth 0, and children of each depth k node are at the depth k + 1.
//
// Example:
// Input: root = [1,2,3,4], x = 4, y = 3
// Output: false
//
// Constraints:
// The number of nodes in the tree is in the range [2, 100].
// 	1 <= Node.val <= 100
// 	Each node has a unique value.
// 	x != y
// 	x and y are exist in the tree.
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
 * @param {number} x
 * @param {number} y
 * @return {boolean}
 */
var isCousins = function(root, x, y) {
    if (root === null) return false;

    const queue = [{ node: root, parent: null, depth: 0 }];
    let xInfo = null;
    let yInfo = null;
    while (queue.length > 0) {
        const { node, parent, depth } = queue.shift();
        if (node.val === x) {
            xInfo = { parent, depth };
        }
        if (node.val === y) {
            yInfo = { parent, depth };
        }
        if (node.left !== null) {
            queue.push({ node: node.left, parent: node, depth: depth + 1 });
        }
        if (node.right !== null) {
            queue.push({ node: node.right, parent: node, depth: depth + 1 });
        }
        if (xInfo !== null && yInfo !== null) {
            break;
        }
    }
    return xInfo !== null && yInfo !== null && xInfo.depth === yInfo.depth && xInfo.parent !== yInfo.parent;
};