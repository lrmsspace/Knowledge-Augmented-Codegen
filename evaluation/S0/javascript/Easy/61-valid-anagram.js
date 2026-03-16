// Source: https://leetcode.com/problems/valid-anagram/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and t, return true if t is an anagram of s, and false otherwise.
//
// Example:
// Input: s = "anagram", t = "nagaram"
//
// Output: true
//
// Constraints:
// 1 <= s.length, t.length <= 5 * 104
// 	s and t consist of lowercase English letters.
//
//
//  
// Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?
//

/**
 * @param {string} s
 * @param {string} t
 * @return {boolean}
 */
var isAnagram = function(s, t) {
    if (s.length !== t.length) {
        return false;
    }
    const count = new Array(26).fill(0);
    for (let i = 0; i < s.length; i++) {
        count[s.charCodeAt(i) - 97]++;
        count[t.charCodeAt(i) - 97]--;
    }
    for (let i = 0; i < 26; i++) {
        if (count[i] !== 0) {
            return false;
        }
    }
    return true;
};