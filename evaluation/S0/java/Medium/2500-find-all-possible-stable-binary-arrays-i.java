// Source: https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/   |   Difficulty: Medium
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
// The two possible stable binary arrays are [1,0] and [0,1], as both arrays have a single 0 and a single 1, and no subarray has a length greater than 2.
//
// Constraints:
// 1 <= zero, one, limit <= 200
//

class Solution {
    public int numberOfStableArrays(int zero, int one, int limit) {
        int MOD = 1_000_000_007;
        long[][] dp = new long[zero + 1][one + 1];
        dp[0][0] = 1;

        for (int z = 0; z <= zero; z++) {
            for (int o = 0; o <= one; o++) {
                for (int len = 1; len <= limit; len++) {
                    if (z - len >= 0) {
                        dp[z][o] = (dp[z][o] + dp[z - len][o]) % MOD;
                    }
                    if (o - len >= 0) {
                        dp[z][o] = (dp[z][o] + dp[z][o - len]) % MOD;
                    }
                }
            }
        }

        return (int) dp[zero][one];         
    }
}
