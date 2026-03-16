// Source: https://leetcode.com/problems/longest-palindromic-substring/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the longest palindromic substring in s.
//
// Example:
// Input: s = "babad"
// Output: "bab"
// Explanation: "aba" is also a valid answer.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consist of only digits and English letters.
//

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n == 0) return "";

        int start = 0, maxLength = 1;

        for (int i = 0; i < n; ++i) {
            // Odd length palindromes
            int left = i, right = i;
            while (left >= 0 && right < n && s[left] == s[right]) {
                if (right - left + 1 > maxLength) {
                    start = left;
                    maxLength = right - left + 1;
                }
                --left;
                ++right;
            }

            // Even length palindromes
            left = i, right = i + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                if (right - left + 1 > maxLength) {
                    start = left;
                    maxLength = right - left + 1;
                }
                --left;
                ++right;
            }
        }

        return s.substr(start, maxLength);          
    }
};
