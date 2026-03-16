// Source: https://leetcode.com/problems/is-subsequence/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
//
// A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
//
// Example:
// Input: s = "abc", t = "ahbgdc"
// Output: true
//
// Constraints:
// 0 <= s.length <= 100
// 	0 <= t.length <= 104
// 	s and t consist only of lowercase English letters.
//
//
//  
// Follow up: Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 109, and you want to check one by one to see if t has its subsequence. In this scenario, how would you change your code?
//

class Solution {
    public boolean isSubsequence(String s, String t) {
        int sLen = s.length();
        int tLen = t.length();
        if (sLen == 0) {
            return true;
        }
        if (tLen == 0) {
            return false;
        }

        int sIndex = 0;
        int tIndex = 0;

        while (tIndex < tLen) {
            if (s.charAt(sIndex) == t.charAt(tIndex)) {
                sIndex++;
                if (sIndex == sLen) {
                    return true;
                }
            }
            tIndex++;
        }

        return false;           
    }
}
