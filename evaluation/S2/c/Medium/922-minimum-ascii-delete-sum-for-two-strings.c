// Source: https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.
//
// Example:
// Input: s1 = "sea", s2 = "eat"
// Output: 231
// Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
// Deleting "t" from "eat" adds 116 to the sum.
// At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
//
// Constraints:
// 1 <= s1.length, s2.length <= 1000
// 	s1 and s2 consist of lowercase English letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumDeleteSum(char* s1, char* s2) {
    int len1 = 0, len2 = 0;
    while (s1[len1]) len1++;
    while (s2[len2]) len2++;

    int dp[len1 + 1][len2 + 1];
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j > 0 ? dp[i][j - 1] + s2[j - 1] : 0;
            } else if (j == 0) {
                dp[i][j] = i > 0 ? dp[i - 1][j] + s1[i - 1] : 0;
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = (dp[i - 1][j] < dp[i][j - 1]) ? (dp[i - 1][j] + s1[i - 1]) : (dp[i][j - 1] + s2[j - 1]);
            }
        }
    }

    return dp[len1][len2];      
}
