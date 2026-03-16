// Source: https://leetcode.com/problems/longest-arithmetic-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.
//
// Note that:
//
//
// 	A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
// 	A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value (for 0 <= i < seq.length - 1).
//
// Example:
// Input: nums = [3,6,9,12]
// Output: 4
// Explanation:  The whole array is an arithmetic sequence with steps of length = 3.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	0 <= nums[i] <= 500
//

int longestArithSeqLength(int* nums, int numsSize) {
    int maxLength = 0;
    int dp[1000][1001] = {0}; // dp[i][d] represents the length of the longest arithmetic subsequence ending at index i with common difference d

    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            int diff = nums[i] - nums[j] + 500; // Shift difference to be non-negative
            dp[i][diff] = dp[j][diff] ? dp[j][diff] + 1 : 2; // If there's already a subsequence, extend it; otherwise start a new one
            if (dp[i][diff] > maxLength) {
                maxLength = dp[i][diff];
            }
        }
    }

    return maxLength;       
}
