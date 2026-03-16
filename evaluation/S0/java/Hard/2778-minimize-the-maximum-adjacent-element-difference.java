// Source: https://leetcode.com/problems/minimize-the-maximum-adjacent-element-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums. Some values in nums are missing and are denoted by -1.
//
// You must choose a pair of positive integers (x, y) exactly once and replace each missing element with either x or y.
//
// You need to minimize the maximum absolute difference between adjacent elements of nums after replacements.
//
// Return the minimum possible difference.
//
// Example:
// Input: nums = [1,2,-1,10,8]
//
// Output: 4
//
// Explanation:
//
// By choosing the pair as (6, 7), nums can be changed to [1, 2, 6, 10, 8].
//
// The absolute differences between adjacent elements are:
//
//
// 	|1 - 2| == 1
// 	|2 - 6| == 4
// 	|6 - 10| == 4
// 	|10 - 8| == 2
//
// Constraints:
// 2 <= nums.length <= 105
// 	nums[i] is either -1 or in the range [1, 109].
//

class Solution {
    public int minDifference(int[] nums) {
        int n = nums.length;
        int left = Integer.MAX_VALUE;
        int right = Integer.MIN_VALUE;
        int maxDiff = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] != -1) {
                if (i > 0 && nums[i - 1] != -1) {
                    maxDiff = Math.max(maxDiff, Math.abs(nums[i] - nums[i - 1]));
                }
                if (i > 0 && nums[i - 1] == -1) {
                    left = Math.min(left, nums[i]);
                    right = Math.max(right, nums[i]);
                }
                if (i < n - 1 && nums[i + 1] == -1) {
                    left = Math.min(left, nums[i]);
                    right = Math.max(right, nums[i]);
                }
            }
        }

        if (left == Integer.MAX_VALUE) {
            return maxDiff;
        }

        int mid = left + (right - left) / 2;
        int potentialMaxDiff = Math.max(Math.abs(mid - left), Math.abs(mid - right));
        return Math.max(maxDiff, potentialMaxDiff);         
    }
}
