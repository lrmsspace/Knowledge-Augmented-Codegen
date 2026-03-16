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

class Solution {
    public int maxPalindromes(String s, int k) {
        int n = s.length();
        boolean[][] isPalindrome = new boolean[n][n];

        // Precompute all palindromic substrings using dynamic programming
        for (int length = 1; length <= n; length++) {
            for (int start = 0; start <= n - length; start++) {
                int end = start + length - 1;
                if (s.charAt(start) == s.charAt(end)) {
                    if (length <= 2) {
                        isPalindrome[start][end] = true;
                    } else {
                        isPalindrome[start][end] = isPalindrome[start + 1][end - 1];
                    }
                }
            }
        }

        // DP array to store the maximum number of non-overlapping palindromic substrings
        int[] dp = new int[n + 1];

        for (int i = 0; i < n; i++) {
            dp[i + 1] = dp[i]; // Carry forward the previous count
            for (int j = i; j >= 0; j--) {
                if (isPalindrome[j][i] && (i - j + 1) >= k) {
                    dp[i + 1] = Math.max(dp[i + 1], dp[j] + 1);
                }
            }
        }

        return dp[n];           
    }
}
