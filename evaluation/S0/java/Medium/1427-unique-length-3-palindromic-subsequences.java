// Source: https://leetcode.com/problems/unique-length-3-palindromic-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the number of unique palindromes of length three that are a subsequence of s.
//
// Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.
//
// A palindrome is a string that reads the same forwards and backwards.
//
// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
//
//
// 	For example, "ace" is a subsequence of "abcde".
//
// Example:
// Input: s = "aabca"
// Output: 3
// Explanation: The 3 palindromic subsequences of length 3 are:
// - "aba" (subsequence of "aabca")
// - "aaa" (subsequence of "aabca")
// - "aca" (subsequence of "aabca")
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of only lowercase English letters.
//

class Solution {
    public int countPalindromicSubsequence(String s) {
        int result = 0;
        for (char c = 'a'; c <= 'z'; c++) {
            int firstIndex = s.indexOf(c);
            int lastIndex = s.lastIndexOf(c);
            if (firstIndex != -1 && lastIndex != -1 && firstIndex < lastIndex) {
                boolean[] seen = new boolean[26];
                for (int i = firstIndex + 1; i < lastIndex; i++) {
                    seen[s.charAt(i) - 'a'] = true;
                }
                for (boolean b : seen) {
                    if (b) {
                        result++;
                    }
                }
            }
        }
        return result;          
    }
}
