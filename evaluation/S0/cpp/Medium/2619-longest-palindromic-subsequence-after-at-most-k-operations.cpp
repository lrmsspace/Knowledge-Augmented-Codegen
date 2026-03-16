// Source: https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k.
//
// In one operation, you can replace the character at any position with the next or previous letter in the alphabet (wrapping around so that 'a' is after 'z'). For example, replacing 'a' with the next letter results in 'b', and replacing 'a' with the previous letter results in 'z'. Similarly, replacing 'z' with the next letter results in 'a', and replacing 'z' with the previous letter results in 'y'.
//
// Return the length of the longest palindromic subsequence of s that can be obtained after performing at most k operations.
//
// Example:
// Input: s = "abced", k = 2
//
// Output: 3
//
// Explanation:
//
//
// 	Replace s[1] with the next letter, and s becomes "acced".
// 	Replace s[4] with the previous letter, and s becomes "accec".
//
//
// The subsequence "ccc" forms a palindrome of length 3, which is the maximum.
//
// Constraints:
// 1 <= s.length <= 200
// 	1 <= k <= 200
// 	s consists of only lowercase English letters.
//

class Solution {
public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = n - 1; i >= 0; --i) {
            dp[i][i] = 0;  // A single character requires 0 operations to be a palindrome
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
                }
            }
        }

        int maxLength = 0;
        for (int length = n; length >= 1; --length) {
            for (int i = 0; i <= n - length; ++i) {
                int j = i + length - 1;
                if (dp[i][j] <= k) {
                    maxLength = length;
                    break;
                }
            }
            if (maxLength > 0) break;
        }

        return maxLength;           
    }
};
