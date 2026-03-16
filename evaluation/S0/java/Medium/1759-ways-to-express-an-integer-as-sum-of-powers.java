// Source: https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/   |   Difficulty: Medium
//
// Problem Description:
// Given two positive integers n and x.
//
// Return the number of ways n can be expressed as the sum of the xth power of unique positive integers, in other words, the number of sets of unique integers [n1, n2, ..., nk] where n = n1x + n2x + ... + nkx.
//
// Since the result can be very large, return it modulo 109 + 7.
//
// For example, if n = 160 and x = 3, one way to express n is n = 23 + 33 + 53.
//
// Example:
// Input: n = 10, x = 2
// Output: 1
// Explanation: We can express n as the following: n = 32 + 12 = 10.
// It can be shown that it is the only way to express 10 as the sum of the 2nd power of unique integers.
//
// Constraints:
// 1 <= n <= 300
// 	1 <= x <= 5
//

class Solution {
    public int numberOfWays(int n, int x) {
        int mod = (int)1e9 + 7;
        int maxBase = (int)Math.pow(n, 1.0 / x);
        int[][] dp = new int[n + 1][maxBase + 1];
        
        for (int i = 0; i <= maxBase; i++) {
            dp[0][i] = 1; // There's one way to form sum 0: using no numbers
        }
        
        for (int sum = 1; sum <= n; sum++) {
            for (int base = 1; base <= maxBase; base++) {
                int power = (int)Math.pow(base, x);
                dp[sum][base] = dp[sum][base - 1]; // Exclude current base
                
                if (sum >= power) {
                    dp[sum][base] = (dp[sum][base] + dp[sum - power][base - 1]) % mod; // Include current base
                }
            }
        }
        
        return dp[n][maxBase];          
    }
}
