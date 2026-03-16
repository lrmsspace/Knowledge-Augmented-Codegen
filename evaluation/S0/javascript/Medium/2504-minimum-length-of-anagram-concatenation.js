// Source: https://leetcode.com/problems/minimum-length-of-anagram-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s, which is known to be a concatenation of anagrams of some string t.
//
// Return the minimum possible length of the string t.
//
// An anagram is formed by rearranging the letters of a string. For example, "aab", "aba", and, "baa" are anagrams of "aab".
//
// Example:
// Input: s = "abba"
//
// Output: 2
//
// Explanation:
//
// One possible string t could be "ba".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consist only of lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var minAnagramLength = function(s) {
    const count = Array(26).fill(0);
    for (const char of s) {
        count[char.charCodeAt(0) - 97]++;
    }
    return Math.max(...count);  
};
