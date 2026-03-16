// Source: https://leetcode.com/problems/even-odd-tree/   |   Difficulty: Medium
//
// Problem Description:
// A binary tree is named Even-Odd if it meets the following conditions:
//
//
// 	The root of the binary tree is at level index 0, its children are at level index 1, their children are at level index 2, etc.
// 	For every even-indexed level, all nodes at the level have odd integer values in strictly increasing order (from left to right).
// 	For every odd-indexed level, all nodes at the level have even integer values in strictly decreasing order (from left to right).
//
//
// Given the root of a binary tree, return true if the binary tree is Even-Odd, otherwise return false.
//
// Example:
// Input: root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
// Output: true
// Explanation: The node values on each level are:
// Level 0: [1]
// Level 1: [10,4]
// Level 2: [3,7,9]
// Level 3: [12,8,6,2]
// Since levels 0 and 2 are all odd and increasing and levels 1 and 3 are all even and decreasing, the tree is Even-Odd.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 106
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
var isEvenOddTree = function(root) {
    if (!root) return true;
    const queue = [root];
    let level = 0;
    while (queue.length > 0) {
        const size = queue.length;
        let prevValue = level % 2 === 0 ? -Infinity : Infinity;
        for (let i = 0; i < size; i++) {
            const node = queue.shift();
            const val = node.val;
            if (level % 2 === 0) {
                if (val % 2 === 0 || val <= prevValue) return false;
            } else {
                if (val % 2 !== 0 || val >= prevValue) return false;
            }
            prevValue = val;
            if (node.left) queue.push(node.left);
            if (node.right) queue.push(node.right);
        }
        level++;
    }
    return true;
};