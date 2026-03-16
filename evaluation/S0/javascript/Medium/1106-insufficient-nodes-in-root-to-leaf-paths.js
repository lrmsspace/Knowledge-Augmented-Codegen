// Source: https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree and an integer limit, delete all insufficient nodes in the tree simultaneously, and return the root of the resulting binary tree.
//
// A node is insufficient if every root to leaf path intersecting this node has a sum strictly less than limit.
//
// A leaf is a node with no children.
//
// Example:
// Input: root = [1,2,3,4,-99,-99,7,8,9,-99,-99,12,13,-99,14], limit = 1
// Output: [1,2,3,4,null,null,7,8,9,null,14]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 5000].
// 	-105 <= Node.val <= 105
// 	-109 <= limit <= 109
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
 * @param {number} limit
 * @return {TreeNode}
 */
var sufficientSubset = function(root, limit) {
    const dfs = (node, currentSum) => {
        if (!node) return null;
        currentSum += node.val;
        if (!node.left && !node.right) {
            return currentSum >= limit ? node : null;
        }
        node.left = dfs(node.left, currentSum);
        node.right = dfs(node.right, currentSum);
        if (!node.left && !node.right) {
            return null;
        }
        return node;
    }
    return dfs(root, 0);    
                
};
