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

int longestSubsequence(int* nums, int numsSize) {
    int dp[numsSize];
    for (int i = 0; i < numsSize; i++) {
        dp[i] = 1;
    }

    int maxLength = 1;

    for (int i = 1; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            int diff = abs(nums[i] - nums[j]);
            int k = j - 1;
            while (k >= 0) {
                int prevDiff = abs(nums[j] - nums[k]);
                if (prevDiff >= diff) {
                    dp[i] = fmax(dp[i], dp[j] + 1);
                    break;
                }
                k--;
            }
        }
        maxLength = fmax(maxLength, dp[i]);
    }

    return maxLength;       
}
