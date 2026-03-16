// Source: https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t consisting of only lowercase English letters.
//
// Return the minimum number of characters that need to be appended to the end of s so that t becomes a subsequence of s.
//
// A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "coaching", t = "coding"
// Output: 4
// Explanation: Append the characters "ding" to the end of s so that s = "coachingding".
// Now, t is a subsequence of s ("coachingding").
// It can be shown that appending any 3 characters to the end of s will never make t a subsequence.
//
// Constraints:
// 1 <= s.length, t.length <= 105
// 	s and t consist only of lowercase English letters.
//

/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var appendCharacters = function(s, t) {
    let sIndex = 0;
    let tIndex = 0;
    while (sIndex < s.length && tIndex < t.length) {
        if (s[sIndex] === t[tIndex]) {
            tIndex++;
        }
        sIndex++;
    }
    return t.length - tIndex;
};