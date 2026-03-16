// Source: https://leetcode.com/problems/all-elements-in-two-binary-search-trees/   |   Difficulty: Medium
//
// Problem Description:
// Given two binary search trees root1 and root2, return a list containing all the integers from both trees sorted in ascending order.
//
// Example:
// Input: root1 = [2,1,4], root2 = [1,0,3]
// Output: [0,1,1,2,3,4]
//
// Constraints:
// The number of nodes in each tree is in the range [0, 5000].
// 	-105 <= Node.val <= 105
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
    public List<Integer> getAllElements(TreeNode root1, TreeNode root2) {
        List<Integer> list1 = new ArrayList<>();
        List<Integer> list2 = new ArrayList<>();
        inorderTraversal(root1, list1);
        inorderTraversal(root2, list2);
        
        return mergeSortedLists(list1, list2);          
    }
}
