// Source: https://leetcode.com/problems/longest-increasing-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the length of the longest strictly increasing subsequence.
//
// Example:
// Input: nums = [10,9,2,5,3,7,101,18]
// Output: 4
// Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
//
// Constraints:
// 1 <= nums.length <= 2500
// 	-104 <= nums[i] <= 104
//
//
//  
// Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
//

class Solution {
    public int lengthOfLIS(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n];
        int maxLength = 0;

        for (int num : nums) {
            int left = 0, right = maxLength;

            // Binary search for the insertion point
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (dp[mid] < num) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            dp[left] = num;

            // If we placed the number at the end, increase the length
            if (left == maxLength) {
                maxLength++;
            }
        }

        return maxLength;           
    }
}
