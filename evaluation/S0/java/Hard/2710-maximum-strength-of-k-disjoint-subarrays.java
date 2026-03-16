// Source: https://leetcode.com/problems/maximum-strength-of-k-disjoint-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums with length n, and a positive odd integer k.
//
// Select exactly k disjoint subarrays sub1, sub2, ..., subk from nums such that the last element of subi appears before the first element of sub{i+1} for all 1 <= i <= k-1. The goal is to maximize their combined strength.
//
// The strength of the selected subarrays is defined as:
//
// strength = k * sum(sub1)- (k - 1) * sum(sub2) + (k - 2) * sum(sub3) - ... - 2 * sum(sub{k-1}) + sum(subk)
//
// where sum(subi) is the sum of the elements in the i-th subarray.
//
// Return the maximum possible strength that can be obtained from selecting exactly k disjoint subarrays from nums.
//
// Note that the chosen subarrays don't need to cover the entire array.
//
// Example:
// Input: nums = [1,2,3,-1,2], k = 3
//
// Output: 22
//
// Explanation:
//
// The best possible way to select 3 subarrays is: nums[0..2], nums[3..3], and nums[4..4]. The strength is calculated as follows:
//
// strength = 3 * (1 + 2 + 3) - 2 * (-1) + 2 = 22
//
// Constraints:
// 1 <= n <= 104
// 	-109 <= nums[i] <= 109
// 	1 <= k <= n
// 	1 <= n * k <= 106
// 	k is odd.
//

class Solution {
    public long maximumStrength(int[] nums, int k) {
        int n = nums.length;
        long[][] dp = new long[k + 1][n + 1];

        for (int i = 1; i <= k; i++) {
            long maxSoFar = Long.MIN_VALUE;
            for (int j = i; j <= n; j++) {
                maxSoFar = Math.max(maxSoFar, dp[i - 1][j - 1] - (long)(i - 1) * nums[j - 1]);
                dp[i][j] = Math.max(dp[i][j - 1], maxSoFar + (long)i * nums[j - 1]);
            }
        }

        return dp[k][n];            
    }
}
