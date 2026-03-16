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

int countVowelPermutation(int n) {
    const int MOD = 1000000007;
    /* dp[i][j]: number of strings of length i ending with vowel j */
    int dp[2][5];
    memset(dp, 0, sizeof(dp));
    /* base case: length 1 */
    for (int j = 0; j < 5; ++j) dp[1 % 2][j] = 1;

    for (int i = 2; i <= n; ++i) {
        dp[i % 2][0] = (dp[(i - 1) % 2][1] + dp[(i - 1) % 2][2] + dp[(i - 1) % 2][4]) % MOD; /* 'a' */
        dp[i % 2][1] = (dp[(i - 1) % 2][0] + dp[(i - 1) % 2][2]) % MOD;                         /* 'e' */
        dp[i % 2][2] = (dp[(i - 1) % 2][1] + dp[(i - 1) % 2][3]) % MOD;                         /* 'i' */
        dp[i % 2][3] = (dp[(i - 1) % 2][2]) % MOD;                                             /* 'o' */
        dp[i % 2][4] = (dp[(i - 1) % 2][2] + dp[(i - 1) % 2][3]) % MOD;                         /* 'u' */
    }

    int result = 0;
    for (int j = 0; j < 5; ++j) {
        result = (result + dp[n % 2][j]) % MOD;
    }
    return result;      
}
