// Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given 3 positive integers zero, one, and limit.
//
// A binary array arr is called stable if:
//
//
// 	The number of occurrences of 0 in arr is exactly zero.
// 	The number of occurrences of 1 in arr is exactly one.
// 	Each subarray of arr with a size greater than limit must contain both 0 and 1.
//
//
// Return the total number of stable binary arrays.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: zero = 1, one = 1, limit = 2
//
// Output: 2
//
// Explanation:
//
// The two possible stable binary arrays are [1,0] and [0,1].
//
// Constraints:
// 1 <= zero, one, limit <= 1000
//

class Solution {
    public int numberOfStableArrays(int zero, int one, int limit) {
        int MOD = 1_000_000_007;
        long[][] dp = new long[zero + 1][one + 1];
        dp[0][0] = 1;

        for (int i = 0; i <= zero; i++) {
            for (int j = 0; j <= one; j++) {
                for (int k = 1; k <= limit && i - k >= 0; k++) {
                    dp[i][j] = (dp[i][j] + dp[i - k][j]) % MOD;
                }
                for (int k = 1; k <= limit && j - k >= 0; k++) {
                    dp[i][j] = (dp[i][j] + dp[i][j - k]) % MOD;
                }
            }
        }

        return (int) dp[zero][one];         
    }
}
