// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and a positive integer k.
//
// Select a set of non-overlapping substrings from the string s that satisfy the following conditions:
//
//
// 	The length of each substring is at least k.
// 	Each substring is a palindrome.
//
//
// Return the maximum number of substrings in an optimal selection.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "abaccdbbd", k = 3
// Output: 2
// Explanation: We can select the substrings underlined in s = "abaccdbbd". Both "aba" and "dbbd" are palindromes and have a length of at least k = 3.
// It can be shown that we cannot find a selection with more than two valid substrings.
//
// Constraints:
// 1 <= k <= s.length <= 2000
// 	s consists of lowercase English letters.
//

int maxPalindromes(char* s, int k) {
    int n = strlen(s);
    int dp[n + 1];
    memset(dp, 0, sizeof(dp));
    for (int center = 0; center < n; center++) {
        // Odd-length palindromes
        for (int radius = 0; center - radius >= 0 && center + radius < n; radius++) {
            if (s[center - radius] != s[center + radius]) break;
            int length = 2 * radius + 1;
            if (length >= k) {
                int start = center - radius;
                dp[start + length] = dp[start + length] > dp[start] + 1 ? dp[start + length] : dp[start] + 1;
            }
        }
        // Even-length palindromes
        for (int radius = 0; center - radius >= 0 && center + radius + 1 < n; radius++) {
            if (s[center - radius] != s[center + radius + 1]) break;
            int length = 2 * radius + 2;
            if (length >= k) {
                int start = center - radius;
                dp[start + length] = dp[start + length] > dp[start] + 1 ? dp[start + length] : dp[start] + 1;
            }
        }
        // Carry forward the maximum count
        dp[center + 1] = dp[center + 1] > dp[center] ? dp[center + 1] : dp[center];
    }
    return dp[n];       
}
