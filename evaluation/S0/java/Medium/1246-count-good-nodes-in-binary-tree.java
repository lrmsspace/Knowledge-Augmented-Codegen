// Source: https://leetcode.com/problems/count-good-nodes-in-binary-tree/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary tree root, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.
//
// Return the number of good nodes in the binary tree.
//
// Example:
// Input: root = [3,1,4,3,null,1,5]
// Output: 4
// Explanation: Nodes in blue are good.
// Root Node (3) is always a good node.
// Node 4 -> (3,4) is the maximum value in the path starting from the root.
// Node 5 -> (3,4,5) is the maximum value in the path
// Node 3 -> (3,1,3) is the maximum value in the path.
//
// Constraints:
// The number of nodes in the binary tree is in the range [1, 10^5].
// 	Each node's value is between [-10^4, 10^4].
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
    public int goodNodes(TreeNode root) {
        return countGoodNodes(root, Integer.MIN_VALUE);         
    }
}
