// Source: https://leetcode.com/problems/number-of-beautiful-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s that consists of the digits '1' to '9' and two integers k and minLength.
//
// A partition of s is called beautiful if:
//
//
// 	s is partitioned into k non-intersecting substrings.
// 	Each substring has a length of at least minLength.
// 	Each substring starts with a prime digit and ends with a non-prime digit. Prime digits are '2', '3', '5', and '7', and the rest of the digits are non-prime.
//
//
// Return the number of beautiful partitions of s. Since the answer may be very large, return it modulo 109 + 7.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "23542185131", k = 3, minLength = 2
// Output: 3
// Explanation: There exists three ways to create a beautiful partition:
// "2354 | 218 | 5131"
// "2354 | 21851 | 31"
// "2354218 | 51 | 31"
//
// Constraints:
// 1 <= k, minLength <= s.length <= 1000
// 	s consists of the digits '1' to '9'.
//

class Solution {
    public int beautifulPartitions(String s, int k, int minLength) {
        int MOD = 1_000_000_007;
        int n = s.length();
        boolean isPrimeStart = isPrime(s.charAt(0));
        boolean isPrimeEnd = !isPrime(s.charAt(n - 1));
        if (!isPrimeStart || !isPrimeEnd) {
            return 0;
        }

        int[] dp = new int[n + 1];
        dp[0] = 1;

        for (int part = 1; part <= k; part++) {
            int[] newDp = new int[n + 1];
            int prefixSum = 0;

            for (int i = minLength * part; i <= n; i++) {
                if (!isPrime(s.charAt(i - 1))) {
                    prefixSum = (prefixSum + dp[i - minLength]) % MOD;
                }
                if (isPrime(s.charAt(i - minLength))) {
                    newDp[i] = prefixSum;
                }
            }
            dp = newDp;
        }

        return dp[n];           
    }
}
