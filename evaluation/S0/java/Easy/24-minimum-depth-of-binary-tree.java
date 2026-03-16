// Source: https://leetcode.com/problems/minimum-depth-of-binary-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary tree, find its minimum depth.
//
// The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
//
// Note: A leaf is a node with no children.
//
// Example:
// Input: root = [3,9,20,null,null,15,7]
// Output: 2
//
// Constraints:
// The number of nodes in the tree is in the range [0, 105].
// 	-1000 <= Node.val <= 1000
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
    public int minDepth(TreeNode root) {
        if (root == null) {
            return 0;
        }

        int leftDepth = minDepth(root.left);
        int rightDepth = minDepth(root.right);

        // If one of the subtrees is missing, we should not consider its depth as 0
        if (leftDepth == 0 || rightDepth == 0) {
            return leftDepth + rightDepth + 1;
        }

        return Math.min(leftDepth, rightDepth) + 1;         
    }
}
