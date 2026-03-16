// Source: https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
// A subsequence sub of nums with length x is called valid if it satisfies:
//
//
// 	(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
//
// Return the length of the longest valid subsequence of nums.
//
// Example:
// Input: nums = [1,2,3,4,5], k = 2
//
// Output: 5
//
// Explanation:
//
// The longest valid subsequence is [1, 2, 3, 4, 5].
//
// Constraints:
// 2 <= nums.length <= 103
// 	1 <= nums[i] <= 107
// 	1 <= k <= 103
//

class Solution {
    public int maximumLength(int[] nums, int k) {
        int n = nums.length;
        int[][] dp = new int[n][k];
        int maxLength = 1;

        for (int i = 0; i < n; i++) {
            int modValue = nums[i] % k;
            dp[i][modValue] = 1; // Each number can start a subsequence

            for (int j = 0; j < i; j++) {
                int sumMod = (nums[i] + nums[j]) % k;
                if (dp[j][sumMod] > 0) {
                    dp[i][modValue] = Math.max(dp[i][modValue], dp[j][sumMod] + 1);
                }
            }

            maxLength = Math.max(maxLength, dp[i][modValue]);
        }

        return maxLength;           
    }
}
