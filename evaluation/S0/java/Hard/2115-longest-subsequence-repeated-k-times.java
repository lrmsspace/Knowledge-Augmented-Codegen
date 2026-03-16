// Source: https://leetcode.com/problems/longest-subsequence-repeated-k-times/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s of length n, and an integer k. You are tasked to find the longest subsequence repeated k times in string s.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// A subsequence seq is repeated k times in the string s if seq * k is a subsequence of s, where seq * k represents a string constructed by concatenating seq k times.
//
//
// 	For example, "bba" is repeated 2 times in the string "bababcba", because the string "bbabba", constructed by concatenating "bba" 2 times, is a subsequence of the string "bababcba".
//
//
// Return the longest subsequence repeated k times in string s. If multiple such subsequences are found, return the lexicographically largest one. If there is no such subsequence, return an empty string.
//
// Example:
// Input: s = "letsleetcode", k = 2
// Output: "let"
// Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
// "let" is the lexicographically largest one.
//
// Constraints:
// n == s.length
// 	2 <= k <= 2000
// 	2 <= n < min(2001, k * 8)
// 	s consists of lowercase English letters.
//

class Solution {
    public String longestSubsequenceRepeatedK(String s, int k) {
        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }

        StringBuilder base = new StringBuilder();
        for (int i = 25; i >= 0; i--) {
            for (int j = 0; j < count[i] / k; j++) {
                base.append((char) (i + 'a'));
            }
        }

        int n = base.length();
        for (int len = n; len >= 1; len--) {
            String candidate = backtrack(base, new StringBuilder(), len, s, k);
            if (!candidate.isEmpty()) {
                return candidate;
            }
        }
        return "";          
    }
}
