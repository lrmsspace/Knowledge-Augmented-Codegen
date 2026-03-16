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
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public int maxProduct(TreeNode root) {
        long MOD = 1_000_000_007;
        List<Long> subtreeSums = new ArrayList<>();
        
        // Helper function to calculate subtree sums
        long totalSum = calculateSubtreeSums(root, subtreeSums);
        
        long maxProduct = 0;
        for (long subSum : subtreeSums) {
            long product = subSum * (totalSum - subSum);
            maxProduct = Math.max(maxProduct, product);
        }
        
        return (int)(maxProduct % MOD);         
    }
}
