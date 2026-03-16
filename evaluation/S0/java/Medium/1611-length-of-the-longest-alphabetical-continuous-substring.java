// Source: https://leetcode.com/problems/length-of-the-longest-alphabetical-continuous-substring/   |   Difficulty: Medium
//
// Problem Description:
// An alphabetical continuous string is a string consisting of consecutive letters in the alphabet. In other words, it is any substring of the string "abcdefghijklmnopqrstuvwxyz".
//
//
// 	For example, "abc" is an alphabetical continuous string, while "acb" and "za" are not.
//
//
// Given a string s consisting of lowercase letters only, return the length of the longest alphabetical continuous substring.
//
// Example:
// Input: s = "abacaba"
// Output: 2
// Explanation: There are 4 distinct continuous substrings: "a", "b", "c" and "ab".
// "ab" is the longest continuous substring.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only English lowercase letters.
//

class Solution {
    public int longestContinuousSubstring(String s) {
        int maxLen = 1;
        int currentLen = 1;

        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i) - s.charAt(i - 1) == 1) {
                currentLen++;
                maxLen = Math.max(maxLen, currentLen);
            } else {
                currentLen = 1;
            }
        }

        return maxLen;          
    }
}
