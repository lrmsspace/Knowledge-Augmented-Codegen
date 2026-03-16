// Source: https://leetcode.com/problems/balanced-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary tree, determine if it is height-balanced.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: true
//
// Constraints:
// The number of nodes in the tree is in the range [0, 5000].
// 	-104 <= Node.val <= 104
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
    public boolean isBalanced(TreeNode root) {
        return checkBalance(root) != -1;            
    }
}
