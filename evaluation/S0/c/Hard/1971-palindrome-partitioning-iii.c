// Source: https://leetcode.com/problems/palindrome-partitioning-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s containing lowercase letters and an integer k. You need to :
//
//
// 	First, change some characters of s to other lowercase English letters.
// 	Then divide s into k non-empty disjoint substrings such that each substring is a palindrome.
//
//
// Return the minimal number of characters that you need to change to divide the string.
//
// Example:
// Input: s = "abc", k = 2
// Output: 1
// Explanation: You can split the string into "ab" and "c", and change 1 character in "ab" to make it palindrome.
//
// Constraints:
// 1 <= k <= s.length <= 100.
// 	s only contains lowercase English letters.
//

int palindromePartition(char* s, int k) {
    int n = strlen(s);
    int dp[n][n];
    memset(dp, 0, sizeof(dp));
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            } else {
                dp[i][j] = dp[i + 1][j - 1] + 1;
            }
        }
    }
    int f[k + 1][n];
    for (int i = 0; i < n; i++) {
        f[1][i] = dp[0][i];
    }
    for (int p = 2; p <= k; p++) {
        for (int i = p - 1; i < n; i++) {
            f[p][i] = n;
            for (int j = p - 2; j < i; j++) {
                if (f[p - 1][j] + dp[j + 1][i] < f[p][i]) {
                    f[p][i] = f[p - 1][j] + dp[j + 1][i];
                }
            }
        }
    }
    return f[k][n - 1];     
}
