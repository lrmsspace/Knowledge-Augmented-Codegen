// Source: https://leetcode.com/problems/find-mode-in-binary-search-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary search tree (BST) with duplicates, return all the mode(s) (i.e., the most frequently occurred element) in it.
//
// If the tree has more than one mode, return them in any order.
//
// Assume a BST is defined as follows:
//
//
// 	The left subtree of a node contains only nodes with keys less than or equal to the node's key.
// 	The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
// 	Both the left and right subtrees must also be binary search trees.
//
// Example:
// Input: root = [1,null,2,2]
// Output: [2]
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	-105 <= Node.val <= 105
//
//
//  
// Follow up: Could you do that without using any extra space? (Assume that the implicit stack space incurred due to recursion does not count).
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
 * @return {number[]}
 */
var findMode = function(root) {

    const freqMap = new Map();
    let maxFreq = 0;
    const modes = [];

    const inorderTraversal = (node) => {
        if (!node) return;
        inorderTraversal(node.left);

        const val = node.val;
        const count = (freqMap.get(val) || 0) + 1;
        freqMap.set(val, count);
        if (count > maxFreq) {
            maxFreq = count;
        }
        inorderTraversal(node.right);
    }
    inorderTraversal(root);

    for (const [val, count] of freqMap.entries()) {
        if (count === maxFreq) {
            modes.push(val);
        }
    }
    return modes;       
};
