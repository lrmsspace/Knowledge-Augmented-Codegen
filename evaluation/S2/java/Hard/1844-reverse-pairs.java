// Source: https://leetcode.com/problems/reverse-pairs/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums, return the number of reverse pairs in the array.
//
// A reverse pair is a pair (i, j) where:
//
//
// 	0 <= i < j < nums.length and
// 	nums[i] > 2 * nums[j].
//
// Example:
// Input: nums = [1,3,2,3,1]
// Output: 2
// Explanation: The reverse pairs are:
// (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
// (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-231 <= nums[i] <= 231 - 1
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int reversePairs(int[] nums) {
        if (nums == null || nums.length == 0) {
            return 0;
        }
        return mergeSort(nums, 0, nums.length - 1);         
    }
}
