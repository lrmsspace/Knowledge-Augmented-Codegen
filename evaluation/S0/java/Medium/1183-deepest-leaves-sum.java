// Source: https://leetcode.com/problems/deepest-leaves-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given the root of a binary tree, return the sum of values of its deepest leaves.
//
// Example:
// Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
// Output: 15
//
// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 	1 <= Node.val <= 100
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
    public int deepestLeavesSum(TreeNode root) {
        if (root == null) {
            return 0;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int deepestLeavesSum = 0;

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            deepestLeavesSum = 0; // Reset sum for the current level

            for (int i = 0; i < levelSize; i++) {
                TreeNode currentNode = queue.poll();
                deepestLeavesSum += currentNode.val;

                if (currentNode.left != null) {
                    queue.offer(currentNode.left);
                }
                if (currentNode.right != null) {
                    queue.offer(currentNode.right);
                }
            }
        }

        return deepestLeavesSum;            
    }
}
