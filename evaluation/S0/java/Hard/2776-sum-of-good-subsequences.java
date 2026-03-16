// Source: https://leetcode.com/problems/sum-of-good-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. A good subsequence is defined as a subsequence of nums where the absolute difference between any two consecutive elements in the subsequence is exactly 1.
//
// Return the sum of all possible good subsequences of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note that a subsequence of size 1 is considered good by definition.
//
// Example:
// Input: nums = [1,2,1]
//
// Output: 14
//
// Explanation:
//
//
// 	Good subsequences are: [1], [2], [1], [1,2], [2,1], [1,2,1].
// 	The sum of elements in these subsequences is 14.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
//

class Solution {
    public int sumOfGoodSubsequences(int[] nums) {
        int MOD = 1_000_000_007;
        int maxNum = 0;
        for (int num : nums) {
            maxNum = Math.max(maxNum, num);
        }

        long[] count = new long[maxNum + 1];
        for (int num : nums) {
            count[num]++;
        }

        long[] dp = new long[maxNum + 1];
        for (int i = 0; i <= maxNum; i++) {
            if (count[i] == 0) continue;

            long ways = modPow(2, count[i], MOD) - 1; // non-empty subsequences of current number

            dp[i] = (dp[i] + ways * (i % MOD)) % MOD; // subsequences with only current number

            if (i > 0) {
                dp[i] = (dp[i] + dp[i - 1] * ways) % MOD; // extend subsequences ending with i-1
            }
            if (i < maxNum) {
                dp[i + 1] = (dp[i + 1] + dp[i] * (modPow(2, count[i + 1], MOD) - 1)) % MOD; // prepare for extending to i+1
            }
        }

        long result = 0;
        for (long val : dp) {
            result = (result + val) % MOD;
        }

        return (int) result;            
    }
}
