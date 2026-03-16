// Source: https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree.
//
// A ZigZag path for a binary tree is defined as follow:
//
//
// 	Choose any node in the binary tree and a direction (right or left).
// 	If the current direction is right, move to the right child of the current node; otherwise, move to the left child.
// 	Change the direction from right to left or from left to right.
// 	Repeat the second and third steps until you can't move in the tree.
//
//
// Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).
//
// Return the longest ZigZag path contained in that tree.
//
// Example:
// Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1]
// Output: 3
// Explanation: Longest ZigZag path in blue nodes (right -> left -> right).
//
// Constraints:
// The number of nodes in the tree is in the range [1, 5 * 104].
// 	1 <= Node.val <= 100
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
var longestZigZag = function(root) {
    let maxLength = 0;
    const dfs = (node, isLeft, length) => {
        if (!node) return;
        maxLength = Math.max(maxLength, length);    
        if (isLeft) {
            dfs(node.left, false, length + 1);
            dfs(node.right, true, 1);
        } else {
            dfs(node.right, true, length + 1);
            dfs(node.left, false, 1);
        }   
    };
    dfs(root, true, 0);
    dfs(root, false, 0);
    return maxLength;   
        
};
