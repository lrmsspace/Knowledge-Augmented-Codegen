// Source: https://leetcode.com/problems/binary-tree-maximum-path-sum/   |   Difficulty: Hard
//
// Problem Description:
// A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.
//
// The path sum of a path is the sum of the node's values in the path.
//
// Given the root of a binary tree, return the maximum path sum of any non-empty path.
//
// Example:
// Input: root = [1,2,3]
// Output: 6
// Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 3 * 104].
// 	-1000 <= Node.val <= 1000
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
var maxPathSum = function(root) {
    let maxSum = -Infinity;
        
    const dfs = (node) => {
        if (!node) return 0;
        const leftMax = Math.max(0, dfs(node.left)); // Max path sum from left subtree
        const rightMax = Math.max(0, dfs(node.right)); // Max path sum from right subtree
        maxSum = Math.max(maxSum, node.val + leftMax + rightMax); // Update global max path sum
        return node.val + Math.max(leftMax, rightMax); // Return max path sum including current node
    };
    
    dfs(root);
    return maxSum;  
        
};
