// Source: https://leetcode.com/problems/regular-expression-matching/   |   Difficulty: Hard
//
// Problem Description:
// Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
//
//
// 	'.' Matches any single character.​​​​
// 	'*' Matches zero or more of the preceding element.
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
// 1 <= s.length <= 20
// 	1 <= p.length <= 20
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters, '.', and '*'.
// 	It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.
//

bool isMatch(char* s, char* p) {
    int slen = strlen(s);
    int plen = strlen(p);
    bool dp[slen + 1][plen + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = true;
    for (int j = 1; j <= plen; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }
    for (int i = 1; i <= slen; i++) {
        for (int j = 1; j <= plen; j++) {
            if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2];
                if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }
    return dp[slen][plen];      
}
