// Source: https://leetcode.com/problems/wildcard-matching/   |   Difficulty: Hard
//
// Problem Description:
// Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
//
//
// 	'?' Matches any single character.
// 	'*' Matches any sequence of characters (including the empty sequence).
//
//
// The matching should cover the entire input string (not partial).
//
// Example:
// Input: s = "aa", p = "a"
// Output: false
// Explanation: "a" does not match the entire string "aa".
//
// Constraints:
// 0 <= s.length, p.length <= 2000
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters, '?' or '*'.
//

bool isMatch(char* s, char* p) {
    int sLen = strlen(s);
    int pLen = strlen(p);
    bool dp[sLen + 1][pLen + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = true;
    for (int j = 1; j <= pLen; ++j) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 1];
        }
    }
    for (int i = 1; i <= sLen; ++i) {
        for (int j = 1; j <= pLen; ++j) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            } else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    return dp[sLen][pLen];      
}
