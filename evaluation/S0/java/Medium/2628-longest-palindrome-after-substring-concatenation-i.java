// Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings, s and t.
//
// You can create a new string by selecting a substring from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.
//
// Return the length of the longest palindrome that can be formed this way.
//
// Example:
// Input: s = "a", t = "a"
//
// Output: 2
//
// Explanation:
//
// Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.
//
// Constraints:
// 1 <= s.length, t.length <= 30
// 	s and t consist of lowercase English letters.
//

class Solution {
    public int longestPalindrome(String s, String t) {
        int maxLength = 0;
        int sLen = s.length();
        int tLen = t.length();

        for (int i = 0; i <= sLen; i++) {
            for (int j = 0; j <= tLen; j++) {
                String combined = s.substring(0, i) + t.substring(j);
                int palindromeLength = getLongestPalindromicSubstringLength(combined);
                maxLength = Math.max(maxLength, palindromeLength);
            }
        }

        return maxLength;           
    }
}
