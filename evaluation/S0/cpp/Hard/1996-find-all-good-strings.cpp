// Source: https://leetcode.com/problems/find-all-good-strings/   |   Difficulty: Hard
//
// Problem Description:
// Given the strings s1 and s2 of size n and the string evil, return the number of good strings.
//
// A good string has size n, it is alphabetically greater than or equal to s1, it is alphabetically smaller than or equal to s2, and it does not contain the string evil as a substring. Since the answer can be a huge number, return this modulo 109 + 7.
//
// Example:
// Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
// Output: 51 
// Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". Then there are 25 good strings starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da".
//
// Constraints:
// s1.length == n
// 	s2.length == n
// 	s1 <= s2
// 	1 <= n <= 500
// 	1 <= evil.length <= 50
// 	All strings consist of lowercase English letters.
//

class Solution {
public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
        const int MOD = 1e9 + 7;
        int m = evil.size();
        
        // Build KMP table for evil string
        vector<int> lps(m, 0);
        for (int i = 1, len = 0; i < m; ) {
            if (evil[i] == evil[len]) {
                lps[i++] = ++len;
            } else if (len) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }
        
        // DP state: dp[pos][matched][isPrefixS1][isPrefixS2]
        vector<vector<vector<vector<int>>>> dp(n + 1, vector<vector<vector<int>>>(m + 1, vector<vector<int>>(2, vector<int>(2, 0))));
        dp[0][0][1][1] = 1;
        
        for (int pos = 0; pos < n; pos++) {
            for (int matched = 0; matched <= m; matched++) {
                for (int isPrefixS1 = 0; isPrefixS1 <= 1; isPrefixS1++) {
                    for (int isPrefixS2 = 0; isPrefixS2 <= 1; isPrefixS2++) {
                        if (dp[pos][matched][isPrefixS1][isPrefixS2] == 0) continue;
                        
                        char startChar = isPrefixS1 ? s1[pos] : 'a';
                        char endChar = isPrefixS2 ? s2[pos] : 'z';
                        
                        for (char c = startChar; c <= endChar; c++) {
                            int nextMatched = matched;
                            while (nextMatched > 0 && evil[nextMatched] != c) {
                                nextMatched = lps[nextMatched - 1];
                            }
                            if (evil[nextMatched] == c) {
                                nextMatched++;
                            }
                            
                            if (nextMatched == m) continue; // evil found
                            
                            int nextIsPrefixS1 = isPrefixS1 && (c == startChar);
                            int nextIsPrefixS2 = isPrefixS2 && (c == endChar);
                            dp[pos + 1][nextMatched][nextIsPrefixS1][nextIsPrefixS2] = (dp[pos + 1][nextMatched][nextIsPrefixS1][nextIsPrefixS2] + dp[pos][matched][isPrefixS1][isPrefixS2]) % MOD; 
                            
                        }
                    }
                }
            }
        }
        
        int result = 0;
        for (int matched = 0; matched < m; matched++) {
            for (int isPrefixS1 = 0; isPrefixS1 <= 1; isPrefixS1++) {
                for (int isPrefixS2 = 0; isPrefixS2 <= 1; isPrefixS2++) {
                    result = (result + dp[n][matched][isPrefixS1][isPrefixS2]) % MOD;
                }
            }
        }
        
        return result;
    }
};