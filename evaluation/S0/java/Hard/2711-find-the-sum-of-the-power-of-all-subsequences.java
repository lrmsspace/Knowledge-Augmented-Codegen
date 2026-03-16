// Source: https://leetcode.com/problems/find-the-sum-of-the-power-of-all-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and a positive integer k.
//
// The power of an array of integers is defined as the number of subsequences with their sum equal to k.
//
// Return the sum of power of all subsequences of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input:   nums = [1,2,3], k = 3 
//
// Output:   6 
//
// Explanation:
//
// There are 5 subsequences of nums with non-zero power:
//
//
// 	The subsequence [1,2,3] has 2 subsequences with sum == 3: [1,2,3] and [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
//
//
// Hence the answer is 2 + 1 + 1 + 1 + 1 = 6.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= nums[i] <= 104
// 	1 <= k <= 100
//

class Solution {
    public int sumOfPower(int[] nums, int k) {
        int mod = (int)1e9 + 7;
        int n = nums.length;
        long[][] dp = new long[n + 1][k + 1];
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            int num = nums[i - 1];
            for (int j = 0; j <= k; j++) {
                dp[i][j] = dp[i - 1][j] * 2 % mod; // Exclude or include the current number
                if (j >= num) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - num]) % mod; // Include current number to form sum j
                }
            }
        }

        long result = 0;
        for (int i = 1; i <= n; i++) {
            result = (result + dp[i][k]) % mod;
        }

        return (int)result;         
    }
}
