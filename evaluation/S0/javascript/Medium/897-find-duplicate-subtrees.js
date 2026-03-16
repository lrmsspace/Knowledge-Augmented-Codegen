// Source: https://leetcode.com/problems/find-duplicate-subtrees/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return all duplicate subtrees.
//
// For each kind of duplicate subtrees, you only need to return the root node of any one of them.
//
// Two trees are duplicate if they have the same structure with the same node values.
//
// Example:
// Input: root = [1,2,3,4,null,2,4,null,null,4]
// Output: [[2,4],[4]]
//
// Constraints:
// The number of the nodes in the tree will be in the range [1, 5000]
// 	-200 <= Node.val <= 200
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
 * @return {TreeNode[]}
 */
var findDuplicateSubtrees = function(root) {
    const map = new Map();
    const result = [];

    const serialize = (node) => {
        if (!node) return '#';
        const serial = `${node.val},${serialize(node.left)},${serialize(node.right)}`;
        map.set(serial, (map.get(serial) || 0) + 1);
        if (map.get(serial) === 2) {
            result.push(node);
        }
        return serial;
    };

    serialize(root);
    return result;
};