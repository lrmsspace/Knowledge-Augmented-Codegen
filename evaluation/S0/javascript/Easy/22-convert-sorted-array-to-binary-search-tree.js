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
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {number[]} nums
 * @return {TreeNode}
 */
var sortedArrayToBST = function(nums) {
    if (!nums.length) return null;
    const mid = Math.floor(nums.length / 2);
    const root = new TreeNode(nums[mid]);
    root.left = sortedArrayToBST(nums.slice(0, mid));
    root.right = sortedArrayToBST(nums.slice(mid + 1));
    return root;
};
