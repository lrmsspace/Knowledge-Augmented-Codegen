// Source: https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/   |   Difficulty: Medium
//
// Problem Description:
// A string s is called good if there are no two different characters in s that have the same frequency.
//
// Given a string s, return the minimum number of characters you need to delete to make s good.
//
// The frequency of a character in a string is the number of times it appears in the string. For example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.
//
// Example:
// Input: s = "aab"
// Output: 0
// Explanation: s is already good.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var minDeletions = function(s) {
    const freq = Array(26).fill(0);
    for (const char of s) {
        freq[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }
    freq.sort((a, b) => b - a);
    let deletions = 0;
    for (let i = 1; i < freq.length; i++) {
        while (freq[i] > 0 && freq[i] >= freq[i - 1]) {
            freq[i]--;
            deletions++;
        }
    }
    return deletions;
};