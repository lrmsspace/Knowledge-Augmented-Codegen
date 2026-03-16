// Source: https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of integers. You are also given a 2D array queries, where queries[i] = [posi, xi].
//
// For query i, we first set nums[posi] equal to xi, then we calculate the answer to query i which is the maximum sum of a subsequence of nums where no two adjacent elements are selected.
//
// Return the sum of the answers to all queries.
//
// Since the final answer may be very large, return it modulo 109 + 7.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [3,5,9], queries = [[1,-2],[0,-3]]
//
// Output: 21
//
// Explanation:
// After the 1st query, nums = [3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 3 + 9 = 12.
// After the 2nd query, nums = [-3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 9.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-105 <= nums[i] <= 105
// 	1 <= queries.length <= 5 * 104
// 	queries[i] == [posi, xi]
// 	0 <= posi <= nums.length - 1
// 	-105 <= xi <= 105
//

class Solution {
    public int maximumSumSubsequence(int[] nums, int[][] queries) {
        final int MOD = 1_000_000_007;
        long totalSum = 0;
        int n = nums.length;

        // Calculate initial maximum sum of non-adjacent elements
        long[] dp = new long[n + 2];
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = Math.max(dp[i + 1], nums[i] + dp[i + 2]);
        }
        totalSum = dp[0];

        long result = 0;

        for (int[] query : queries) {
            int pos = query[0];
            int newValue = query[1];
            int oldValue = nums[pos];

            if (oldValue == newValue) {
                result = (result + totalSum) % MOD;
                continue;
            }

            // Update nums array
            nums[pos] = newValue;

            // Recalculate maximum sum after the update
            dp = new long[n + 2];
            for (int i = n - 1; i >= 0; i--) {
                dp[i] = Math.max(dp[i + 1], nums[i] + dp[i + 2]);
            }
            totalSum = dp[0];

            result = (result + totalSum) % MOD;
        }

        return (int) result;            
    }
}
