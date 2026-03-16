// Source: https://leetcode.com/problems/length-of-the-longest-subsequence-that-sums-to-target/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of integers nums, and an integer target.
//
// Return the length of the longest subsequence of nums that sums up to target. If no such subsequence exists, return -1.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [1,2,3,4,5], target = 9
// Output: 3
// Explanation: There are 3 subsequences with a sum equal to 9: [4,5], [1,3,5], and [2,3,4]. The longest subsequences are [1,3,5], and [2,3,4]. Hence, the answer is 3.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	1 <= target <= 1000
//

int lengthOfLongestSubsequence(int* nums, int numsSize, int target) {
    int dp[target + 1];
    for (int i = 0; i <= target; i++) {
        dp[i] = -1;
    }
    dp[0] = 0;

    for (int i = 0; i < numsSize; i++) {
        for (int j = target; j >= nums[i]; j--) {
            if (dp[j - nums[i]] != -1) {
                dp[j] = dp[j] > dp[j - nums[i]] + 1 ? dp[j] : dp[j - nums[i]] + 1;
            }
        }
    }

    return dp[target];      
}
