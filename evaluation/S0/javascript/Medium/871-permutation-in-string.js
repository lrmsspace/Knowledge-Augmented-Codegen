// Source: https://leetcode.com/problems/permutation-in-string/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
//
// In other words, return true if one of s1's permutations is the substring of s2.
//
// Example:
// Input: s1 = "ab", s2 = "eidbaooo"
// Output: true
// Explanation: s2 contains one permutation of s1 ("ba").
//
// Constraints:
// 1 <= s1.length, s2.length <= 104
// 	s1 and s2 consist of lowercase English letters.
//

/**
 * @param {string} s1
 * @param {string} s2
 * @return {boolean}
 */
var checkInclusion = function(s1, s2) {
    const charCount = Array(26).fill(0);
    for (const char of s1) {
        charCount[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }
    const windowCount = Array(26).fill(0);
    let left = 0;
    for (let right = 0; right < s2.length; right++) {
        windowCount[s2[right].charCodeAt(0) - 'a'.charCodeAt(0)]++;
        if (right - left + 1 > s1.length) {
            windowCount[s2[left].charCodeAt(0) - 'a'.charCodeAt(0)]--;
            left++;
        }
        if (right - left + 1 === s1.length && windowCount.every((count, i) => count === charCount[i])) {
            return true;
        }
    }
    return false;
};