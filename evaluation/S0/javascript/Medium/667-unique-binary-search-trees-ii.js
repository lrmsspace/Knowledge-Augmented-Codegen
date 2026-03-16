// Source: https://leetcode.com/problems/unique-binary-search-trees-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.
//
// Example:
// Input: n = 3
// Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
//
// Constraints:
// 1 <= n <= 8
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
 * @param {number} n
 * @return {TreeNode[]}
 */
var generateTrees = function(n) {
    if (n === 0) return [];

    const buildTrees = (start, end) => {
        const result = [];
        if (start > end) {
            result.push(null);
            return result;
        }
        for (let i = start; i <= end; i++) {
            const leftTrees = buildTrees(start, i - 1);
            const rightTrees = buildTrees(i + 1, end);

            for (const left of leftTrees) {
                for (const right of rightTrees) {
                    const root = new TreeNode(i);
                    root.left = left;
                    root.right = right;
                    result.push(root);
                }
            }
        }
        return result;
    };

    return buildTrees(1, n);
};