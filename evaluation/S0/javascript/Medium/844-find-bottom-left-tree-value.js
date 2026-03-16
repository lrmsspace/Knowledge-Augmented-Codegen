// Source: https://leetcode.com/problems/find-bottom-left-tree-value/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the leftmost value in the last row of the tree.
//
// Example:
// Input: root = [2,1,3]
// Output: 1
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-231 <= Node.val <= 231 - 1
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
var findBottomLeftValue = function(root) {
    let queue = [root];
    let leftmostValue = root.val;
    while (queue.length > 0) {
        const levelSize = queue.length;
        leftmostValue = queue[0].val;
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
    }
    return leftmostValue;
};