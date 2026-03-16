// Source: https://leetcode.com/problems/count-vowels-permutation/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, your task is to count how many strings of length n can be formed under the following rules:
//
//
// 	Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
// 	Each vowel 'a' may only be followed by an 'e'.
// 	Each vowel 'e' may only be followed by an 'a' or an 'i'.
// 	Each vowel 'i' may not be followed by another 'i'.
// 	Each vowel 'o' may only be followed by an 'i' or a 'u'.
// 	Each vowel 'u' may only be followed by an 'a'.
//
//
// Since the answer may be too large, return it modulo 10^9 + 7.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
//
// Constraints:
// 1 <= n <= 2 * 10^4
//

class Solution {
    public int countVowelPermutation(int n) {
        long mod = 1_000_000_007;
        long[][] dp = new long[n + 1][5];

        // Base case: For strings of length 1, there's one way to end with each vowel
        for (int j = 0; j < 5; j++) {
            dp[1][j] = 1;
        }

        // Fill the DP table
        for (int i = 2; i <= n; i++) {
            dp[i][0] = (dp[i - 1][1] + dp[i - 1][2] + dp[i - 1][4]) % mod; // 'a' can follow 'e', 'i', 'u'
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % mod;               // 'e' can follow 'a', 'i'
            dp[i][2] = (dp[i - 1][1] + dp[i - 1][3]) % mod;               // 'i' can follow 'e', 'o'
            dp[i][3] = dp[i - 1][2] % mod;                               // 'o' can follow 'i'
            dp[i][4] = (dp[i - 1][2] + dp[i - 1][3]) % mod;               // 'u' can follow 'i', 'o'
        }

        // Sum all the ways to end with each vowel for strings of length n
        long result = 0;
        for (int j = 0; j < 5; j++) {
            result = (result + dp[n][j]) % mod;
        }

        return (int) result;                    
    }
}
