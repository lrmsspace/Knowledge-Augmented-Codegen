// Source: https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/   |   Difficulty: Easy
//
// Problem Description:
// Given a circular array nums, find the maximum absolute difference between adjacent elements.
//
// Note: In a circular array, the first and last elements are adjacent.
//
// Example:
// Input: nums = [1,2,4]
//
// Output: 3
//
// Explanation:
//
// Because nums is circular, nums[0] and nums[2] are adjacent. They have the maximum absolute difference of |4 - 1| = 3.
//
// Constraints:
// 2 <= nums.length <= 100
// 	-100 <= nums[i] <= 100
//

class Solution {
    public int maxAdjacentDistance(int[] nums) {
        int maxDiff = 0;
        int n = nums.length;

        for (int i = 0; i < n; i++) {
            int nextIndex = (i + 1) % n; // Wrap around to the start for the last element
            int currentDiff = Math.abs(nums[i] - nums[nextIndex]);
            maxDiff = Math.max(maxDiff, currentDiff);
        }

        return maxDiff;         
    }
}
