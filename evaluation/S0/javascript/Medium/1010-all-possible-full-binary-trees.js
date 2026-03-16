// Source: https://leetcode.com/problems/all-possible-full-binary-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each tree in the answer must have Node.val == 0.
//
// Each element of the answer is the root node of one possible tree. You may return the final list of trees in any order.
//
// A full binary tree is a binary tree where each node has exactly 0 or 2 children.
//
// Example:
// Input: n = 7
// Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
//
// Constraints:
// 1 <= n <= 20
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
var allPossibleFBT = function(n) {
    if (n % 2 === 0) return [];
    const memo = new Map();

    function buildTrees(nodes) {
        if (memo.has(nodes)) return memo.get(nodes);
        if (nodes === 1) return [new TreeNode(0)];
        const result = [];
        for (let leftNodes = 1; leftNodes < nodes; leftNodes += 2) {
            const rightNodes = nodes - 1 - leftNodes;
            const leftSubtrees = buildTrees(leftNodes);
            const rightSubtrees = buildTrees(rightNodes);
            for (const left of leftSubtrees) {
                for (const right of rightSubtrees) {
                    const root = new TreeNode(0);
                    root.left = left;
                    root.right = right;
                    result.push(root);
                }
            }
        }
        memo.set(nodes, result);
        return result;
    }
    return buildTrees(n);
};
