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

int countSubstrings(char* s) {
    int n = 0;
    for (char* p = s; *p; p++) {
        // Odd-length palindromes
        for (char* l = p, *r = p; l >= s && *r; l--, r++) {
            if (*l != *r) break;
            n++;
        }
        // Even-length palindromes
        for (char* l = p, *r = p + 1; l >= s && *r; l--, r++) {
            if (*l != *r) break;
            n++;
        }
    }
    return n;       
}
