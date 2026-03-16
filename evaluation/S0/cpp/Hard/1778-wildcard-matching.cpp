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

class Solution {
public:
    bool isMatch(string s, string p) {
        int sLen = s.length();
        int pLen = p.length();
        
        // dp[i][j]: whether s[0..i-1] matches p[0..j-1]
        vector<vector<bool>> dp(sLen + 1, vector<bool>(pLen + 1, false));
        dp[0][0] = true;  // empty matches empty
        
        // Initialize first row (s is empty)
        for (int j = 1; j <= pLen; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 1];
            }
        }
        
        for (int i = 1; i <= sLen; i++) {
            for (int j = 1; j <= pLen; j++) {
                if (p[j - 1] == '*') {
                    // '*' matches empty sequence or any sequence
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                    // '?' matches any single character or exact match
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        
        return dp[sLen][pLen];          
    }
};
