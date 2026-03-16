// Source: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.
//
// Example:
// Input: root = [5,3,6,2,4,null,7], k = 9
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-104 <= Node.val <= 104
// 	root is guaranteed to be a valid binary search tree.
// 	-105 <= k <= 105
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
 * @param {number} k
 * @return {boolean}
 */
var findTarget = function(root, k) {
    const set = new Set();

    const dfs = (node) => {
        if (!node) return false;
        if (set.has(k - node.val)) return true;
        set.add(node.val);
        return dfs(node.left) || dfs(node.right);
    }
    return dfs(root);           
};
