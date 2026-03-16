// Source: https://leetcode.com/problems/n-ary-tree-level-order-traversal/   |   Difficulty: Medium
//
// Problem Description:
// Given an n-ary tree, return the level order traversal of its nodes' values.
//
// Nary-Tree input serialization is represented in their level order traversal, each group of children is separated by the null value (See examples).
//
// Example:
// Input: root = [1,null,3,2,4,null,5,6]
// Output: [[1],[3,2,4],[5,6]]
//
// Constraints:
// The height of the n-ary tree is less than or equal to 1000
// 	The total number of nodes is between [0, 104]
//

/**
 * // Definition for a _Node.
 * function _Node(val,children) {
 *    this.val = val;
 *    this.children = children;
 * };
 */

/**
 * @param {_Node|null} root
 * @return {number[][]}
 */
var levelOrder = function(root) {
    if (!root) return [];

    const result = [];
    const queue = [root];
    while (queue.length > 0) {
        const levelSize = queue.length;
        const currentLevel = [];
        for (let i = 0; i < levelSize; i++) {
            const node = queue.shift();
            currentLevel.push(node.val);
            for (const child of node.children) {
                queue.push(child);
            }
        }
        result.push(currentLevel);
    }
    return result;
};