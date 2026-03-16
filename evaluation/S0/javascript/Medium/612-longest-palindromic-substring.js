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

/**
 * @param {string} s
 * @return {string}
 */
var longestPalindrome = function(s) {
    if (s.length < 1) return "";

    let start = 0;
    let end = 0;   
    for (let i = 0; i < s.length; i++) {
        let len1 = expandAroundCenter(s, i, i);       
        let len2 = expandAroundCenter(s, i, i + 1); 
        let len = Math.max(len1, len2);     
        if (len > end - start) {
            start = i - Math.floor((len - 1) / 2);
            end = i + Math.floor(len / 2);
        }   
    }
    return s.substring(start, end + 1);
};      
