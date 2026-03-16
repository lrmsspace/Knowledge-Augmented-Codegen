// Source: https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and two integers left and right, return the number of contiguous non-empty subarrays such that the value of the maximum array element in that subarray is in the range [left, right].
//
// The test cases are generated so that the answer will fit in a 32-bit integer.
//
// Example:
// Input: nums = [2,1,4,3], left = 2, right = 3
// Output: 3
// Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	0 <= left <= right <= 109
//

class Solution {
    public int numSubarrayBoundedMax(int[] nums, int left, int right) {
        return count(nums, right) - count(nums, left - 1);          
    }
}
