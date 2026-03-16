// Source: https://leetcode.com/problems/split-array-largest-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
//
// Return the minimized largest sum of the split.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: nums = [7,2,5,10,8], k = 2
// Output: 18
// Explanation: There are four ways to split nums into two subarrays.
// The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] <= 106
// 	1 <= k <= min(50, nums.length)
//

class Solution {
    public int splitArray(int[] nums, int k) {
        int left = 0, right = 0;
        for (int num : nums) {
            left = Math.max(left, num);
            right += num;
        }

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canSplit(nums, k, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;            
    }
}
