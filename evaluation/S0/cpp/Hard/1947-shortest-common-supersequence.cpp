// Source: https://leetcode.com/problems/shortest-common-supersequence/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.
//
// A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.
//
// Example:
// Input: str1 = "abac", str2 = "cab"
// Output: "cabac"
// Explanation: 
// str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
// str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
// The answer provided is the shortest such string that satisfies these properties.
//
// Constraints:
// 1 <= str1.length, str2.length <= 1000
// 	str1 and str2 consist of lowercase English letters.
//

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.size();
        int n = str2.size();
        
        // Compute LCS DP table
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Reconstruct SCS from LCS DP table
        string scs;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                scs.push_back(str1[i - 1]);
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                scs.push_back(str1[i - 1]);
                i--;
            } else {
                scs.push_back(str2[j - 1]);
                j--;
            }
        }
        
        while (i > 0) {
            scs.push_back(str1[i - 1]);
            i--;
        }
        
        while (j > 0) {
            scs.push_back(str2[j - 1]);
            j--;
        }
        
        reverse(scs.begin(), scs.end());
        return scs;         
    }
};
