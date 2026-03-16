// Source: https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/   |   Difficulty: Medium
//
// Problem Description:
// You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. You are also given an integer startValue representing the value of the start node s, and a different integer destValue representing the value of the destination node t.
//
// Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a string consisting of only the uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:
//
//
// 	'L' means to go from a node to its left child node.
// 	'R' means to go from a node to its right child node.
// 	'U' means to go from a node to its parent node.
//
//
// Return the step-by-step directions of the shortest path from node s to node t.
//
// Example:
// Input: root = [5,1,2,3,null,6,4], startValue = 3, destValue = 6
// Output: "UURL"
// Explanation: The shortest path is: 3 → 1 → 5 → 2 → 6.
//
// Constraints:
// The number of nodes in the tree is n.
// 	2 <= n <= 105
// 	1 <= Node.val <= n
// 	All the values in the tree are unique.
// 	1 <= startValue, destValue <= n
// 	startValue != destValue
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
    public String getDirections(TreeNode root, int startValue, int destValue) {
        StringBuilder startPath = new StringBuilder();
        StringBuilder destPath = new StringBuilder();
        findPath(root, startValue, startPath);
        findPath(root, destValue, destPath);

        int i = 0;
        while (i < startPath.length() && i < destPath.length() && startPath.charAt(i) == destPath.charAt(i)) {
            i++;
        }

        StringBuilder result = new StringBuilder();
        for (int j = i; j < startPath.length(); j++) {
            result.append('U');
        }
        result.append(destPath.substring(i));

        return result.toString();           
    }
}
