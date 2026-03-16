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

class Solution {
public:
    int palindromePartition(string s, int k) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Precompute the cost to convert s[i..j] to a palindrome
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
        
        // dp2[i][k]: minimum changes to partition s[0..i] into k palindromic substrings
        vector<vector<int>> dp2(n, vector<int>(k + 1, INT_MAX));
        
        for (int i = 0; i < n; i++) {
            dp2[i][1] = dp[0][i];  // Base case: one substring
            for (int j = 1; j < i + 1; j++) {
                for (int p = 2; p <= min(k, j + 1); p++) {
                    if (dp2[j - 1][p - 1] != INT_MAX) {
                        dp2[i][p] = min(dp2[i][p], dp2[j - 1][p - 1] + dp[j][i]);
                    }
                }
            }
        }
        
        return dp2[n - 1][k];           
    }
};
