// Source: https://leetcode.com/problems/palindromic-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the number of palindromic substrings in it.
//
// A string is a palindrome when it reads the same backward as forward.
//
// A substring is a contiguous sequence of characters within the string.
//
// Example:
// Input: s = "abc"
// Output: 3
// Explanation: Three palindromic strings: "a", "b", "c".
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters.
//

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int count = 0;

        // Check for odd-length palindromes
        for (int center = 0; center < n; ++center) {
            int left = center, right = center;
            while (left >= 0 && right < n && s[left] == s[right]) {
                count++;
                left--;
                right++;
            }
        }

        // Check for even-length palindromes
        for (int center = 0; center < n - 1; ++center) {
            int left = center, right = center + 1;
            while (left >= 0 && right < n && s[left] == s[right]) {
                count++;
                left--;
                right++;
            }
        }

        return count;           
    }
};
