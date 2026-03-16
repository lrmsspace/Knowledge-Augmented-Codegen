// Source: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums where the elements are sorted in ascending order, convert it to a height-balanced binary search tree.
//
// Example:
// Input: nums = [-10,-3,0,5,9]
// Output: [0,-3,9,-10,null,5]
// Explanation: [0,-10,5,null,-3,null,9] is also accepted:
//
// Constraints:
// 1 <= nums.length <= 104
// 	-104 <= nums[i] <= 104
// 	nums is sorted in a strictly increasing order.
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
    public TreeNode sortedArrayToBST(int[] nums) {
        return buildBST(nums, 0, nums.length - 1);          
    }
}
