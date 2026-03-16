// Source: https://leetcode.com/problems/even-odd-tree/   |   Difficulty: Medium
//
// Problem Description:
// A binary tree is named Even-Odd if it meets the following conditions:
//
//
// 	The root of the binary tree is at level index 0, its children are at level index 1, their children are at level index 2, etc.
// 	For every even-indexed level, all nodes at the level have odd integer values in strictly increasing order (from left to right).
// 	For every odd-indexed level, all nodes at the level have even integer values in strictly decreasing order (from left to right).
//
//
// Given the root of a binary tree, return true if the binary tree is Even-Odd, otherwise return false.
//
// Example:
// Input: root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
// Output: true
// Explanation: The node values on each level are:
// Level 0: [1]
// Level 1: [10,4]
// Level 2: [3,7,9]
// Level 3: [12,8,6,2]
// Since levels 0 and 2 are all odd and increasing and levels 1 and 3 are all even and decreasing, the tree is Even-Odd.
//
// Constraints:
// The number of nodes in the tree is in the range [1, 105].
// 	1 <= Node.val <= 106
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
    public boolean isEvenOddTree(TreeNode root) {
        if (root == null) return true;

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int level = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            int prevValue = level % 2 == 0 ? Integer.MIN_VALUE : Integer.MAX_VALUE;

            for (int i = 0; i < size; i++) {
                TreeNode currentNode = queue.poll();
                int currentValue = currentNode.val;

                // Check for even-indexed levels
                if (level % 2 == 0) {
                    if (currentValue % 2 == 0 || currentValue <= prevValue) {
                        return false;
                    }
                } 
                // Check for odd-indexed levels
                else {
                    if (currentValue % 2 != 0 || currentValue >= prevValue) {
                        return false;
                    }
                }

                prevValue = currentValue;

                if (currentNode.left != null) {
                    queue.offer(currentNode.left);
                }
                if (currentNode.right != null) {
                    queue.offer(currentNode.right);
                }
            }
            level++;
        }

        return true;            
    }
}
