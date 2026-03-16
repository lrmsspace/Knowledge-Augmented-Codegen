// Source: https://leetcode.com/problems/sum-root-to-leaf-numbers/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree containing digits from 0 to 9 only.
//
// Each root-to-leaf path in the tree represents a number.
//
//
// 	For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
//
//
// Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer will fit in a 32-bit integer.
//
// A leaf node is a node with no children.
//
// Example:
// Input: root = [1,2,3]
// Output: 25
// Explanation:
// The root-to-leaf path 1->2 represents the number 12.
// The root-to-leaf path 1->3 represents the number 13.
// Therefore, sum = 12 + 13 = 25.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	0 <= Node.val <= 9
// 	The depth of the tree will not exceed 10.
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
var sumNumbers = function(root) {
    let totalSum = 0;

    const dfs = (node, currentNumber) => {
        if (!node) return;
        currentNumber = currentNumber * 10 + node.val;
        if (!node.left && !node.right) {
            totalSum += currentNumber;
            return;
        }
        dfs(node.left, currentNumber);
        dfs(node.right, currentNumber);
    };
    dfs(root, 0);
    return totalSum;
};
