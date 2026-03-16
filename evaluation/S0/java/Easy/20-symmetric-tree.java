// Source: https://leetcode.com/problems/symmetric-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
//
// Example:
// Input: root = [1,2,2,3,4,4,3]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [1, 1000].
// 	-100 <= Node.val <= 100
//
//
//  
// Follow up: Could you solve it both recursively and iteratively?
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
    public boolean isSymmetric(TreeNode root) {
        return isMirror(root, root);            
    }
}
