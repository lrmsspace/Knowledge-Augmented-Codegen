// Source: https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s. In one step you can insert any character at any index of the string.
//
// Return the minimum number of steps to make s palindrome.
//
// A Palindrome String is one that reads the same backward as well as forward.
//
// Example:
// Input: s = "zzazz"
// Output: 0
// Explanation: The string "zzazz" is already palindrome we do not need any insertions.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of lowercase English letters.
//

class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
                }
            }
        }
        
        return dp[0][n - 1];            
    }
};
