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

/**
 * @param {string} s
 * @return {number}
 */
var countPalindromicSubsequence = function(s) {
    const seen = new Set();
    const n = s.length;
    for (let i = 1; i < n - 1; i++) {
        const leftChars = new Set();
        const rightChars = new Set();
        for (let j = 0; j < i; j++) {
            leftChars.add(s[j]);
        }
        for (let k = i + 1; k < n; k++) {
            rightChars.add(s[k]);
        }
        for (const char of leftChars) {
            if (rightChars.has(char)) {
                seen.add(char + s[i] + char);
            }
        }
    }   
    return seen.size;   
};
