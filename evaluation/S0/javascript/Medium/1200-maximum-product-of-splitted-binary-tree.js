// Source: https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, split the binary tree into two subtrees by removing one edge such that the product of the sums of the subtrees is maximized.
//
// Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it modulo 109 + 7.
//
// Note that you need to maximize the answer before taking the mod and not after taking it.
//
// Example:
// Input: root = [1,2,3,4,5,6]
// Output: 110
// Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)
//
// Constraints:
// The number of nodes in the tree is in the range [2, 5 * 104].
// 	1 <= Node.val <= 104
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
var maxProduct = function(root) {
    
    const MOD = 1e9 + 7;
    let totalSum = 0;
    let maxProd = 0;

    // First pass: Calculate total sum of all nodes
    const calculateTotalSum = (node) => {
        if (!node) return 0;
        totalSum += node.val;
        calculateTotalSum(node.left);
        calculateTotalSum(node.right);
    };
    calculateTotalSum(root);

    // Second pass: Calculate subtree sums and find max product



    const calculateSubtreeSum = (node) => {
        if (!node) return 0;
        const leftSum = calculateSubtreeSum(node.left);
        const rightSum = calculateSubtreeSum(node.right);
        const subtreeSum = node.val + leftSum + rightSum;
        const product = subtreeSum * (totalSum - subtreeSum);
        maxProd = Math.max(maxProd, product);
        return subtreeSum;
    };
    calculateSubtreeSum(root);
    return maxProd % MOD;
        
};
