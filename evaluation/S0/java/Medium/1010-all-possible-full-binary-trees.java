// Source: https://leetcode.com/problems/all-possible-full-binary-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each tree in the answer must have Node.val == 0.
//
// Each element of the answer is the root node of one possible tree. You may return the final list of trees in any order.
//
// A full binary tree is a binary tree where each node has exactly 0 or 2 children.
//
// Example:
// Input: n = 7
// Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
//
// Constraints:
// 1 <= n <= 20
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
    public List<TreeNode> allPossibleFBT(int n) {
        if (n % 2 == 0) {
            return new ArrayList<>();
        }

        Map<Integer, List<TreeNode>> memo = new HashMap<>();
        return buildTrees(n, memo);         
    }
}
