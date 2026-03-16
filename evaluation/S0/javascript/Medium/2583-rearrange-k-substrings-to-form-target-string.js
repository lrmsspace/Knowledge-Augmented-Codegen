// Source: https://leetcode.com/problems/rearrange-k-substrings-to-form-target-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t, both of which are anagrams of each other, and an integer k.
//
// Your task is to determine whether it is possible to split the string s into k equal-sized substrings, rearrange the substrings, and concatenate them in any order to create a new string that matches the given string t.
//
// Return true if this is possible, otherwise, return false.
//
// An anagram is a word or phrase formed by rearranging the letters of a different word or phrase, using all the original letters exactly once.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "abcd", t = "cdab", k = 2
//
// Output: true
//
// Explanation:
//
//
// 	Split s into 2 substrings of length 2: ["ab", "cd"].
// 	Rearranging these substrings as ["cd", "ab"], and then concatenating them results in "cdab", which matches t.
//
// Constraints:
// 1 <= s.length == t.length <= 2 * 105
// 	1 <= k <= s.length
// 	s.length is divisible by k.
// 	s and t consist only of lowercase English letters.
// 	The input is generated such that s and t are anagrams of each other.
//

/**
 * @param {string} s
 * @param {string} t
 * @param {number} k
 * @return {boolean}
 */
var isPossibleToRearrange = function(s, t, k) {
    const n = s.length;
    const freqS = Array(26).fill(0);
    const freqT = Array(26).fill(0);
    for (let i = 0; i < n; i++) {
        freqS[s.charCodeAt(i) - 97]++;
        freqT[t.charCodeAt(i) - 97]++;
    }
    const substringLength = n / k;
    for (let i = 0; i < 26; i++) {
        if (freqS[i] % substringLength !== freqT[i] % substringLength) {
            return false;
        }
    }
    return true;
};