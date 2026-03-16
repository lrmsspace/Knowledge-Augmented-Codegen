// Source: https://leetcode.com/problems/longest-subsequence-with-decreasing-adjacent-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums.
//
// Your task is to find the length of the longest subsequence seq of nums, such that the absolute differences between consecutive elements form a non-increasing sequence of integers. In other words, for a subsequence seq0, seq1, seq2, ..., seqm of nums, |seq1 - seq0| >= |seq2 - seq1| >= ... >= |seqm - seqm - 1|.
//
// Return the length of such a subsequence.
//
// Example:
// Input: nums = [16,6,3]
//
// Output: 3
//
// Explanation: 
//
// The longest subsequence is [16, 6, 3] with the absolute adjacent differences [10, 3].
//
// Constraints:
// 2 <= nums.length <= 104
// 	1 <= nums[i] <= 300
//

class Solution {
    public int longestSubsequence(int[] nums) {
        int n = nums.length;
        int[][] dp = new int[n][301];
        int maxLength = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= 300; j++) {
                dp[i][j] = 1; // Each element can form a subsequence of length 1
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int diff = Math.abs(nums[i] - nums[j]);
                for (int k = diff; k <= 300; k++) {
                    dp[i][diff] = Math.max(dp[i][diff], dp[j][k] + 1);
                }
            }
            for (int k = 0; k <= 300; k++) {
                maxLength = Math.max(maxLength, dp[i][k]);
            }
        }

        return maxLength;           
    }
}
