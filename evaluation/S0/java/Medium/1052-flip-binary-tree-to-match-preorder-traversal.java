// Source: https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with n nodes, where each node is uniquely assigned a value from 1 to n. You are also given a sequence of n values voyage, which is the desired pre-order traversal of the binary tree.
//
// Any node in the binary tree can be flipped by swapping its left and right subtrees. For example, flipping node 1 will have the following effect:
//
// Flip the smallest number of nodes so that the pre-order traversal of the tree matches voyage.
//
// Return a list of the values of all flipped nodes. You may return the answer in any order. If it is impossible to flip the nodes in the tree to make the pre-order traversal match voyage, return the list [-1].
//
// Example:
// Input: root = [1,2], voyage = [2,1]
// Output: [-1]
// Explanation: It is impossible to flip the nodes such that the pre-order traversal matches voyage.
//
// Constraints:
// The number of nodes in the tree is n.
// 	n == voyage.length
// 	1 <= n <= 100
// 	1 <= Node.val, voyage[i] <= n
// 	All the values in the tree are unique.
// 	All the values in voyage are unique.
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
    public List<Integer> flipMatchVoyage(TreeNode root, int[] voyage) {
        List<Integer> result = new ArrayList<>();
        if (dfs(root, voyage, result, new int[]{0})) {
            return result;
        }
        return Arrays.asList(-1);           
    }
}
