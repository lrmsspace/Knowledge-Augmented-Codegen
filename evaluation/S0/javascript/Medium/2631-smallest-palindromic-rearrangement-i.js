// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a palindromic string s.
//
// Return the lexicographically smallest palindromic permutation of s.
//
// Example:
// Input: s = "z"
//
// Output: "z"
//
// Explanation:
//
// A string of only one character is already the lexicographically smallest palindrome.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
//

/**
 * @param {string} s
 * @return {string}
 */
var smallestPalindrome = function(s) {
    const count = new Array(26).fill(0);
    for (const char of s) {
        count[char.charCodeAt(0) - 97]++;
    }
    let half = '';
    let middle = '';
    for (let i = 0; i < 26; i++) {
        if (count[i] % 2 === 1) {
            middle = String.fromCharCode(i + 97);
        }
        half += String.fromCharCode(i + 97).repeat(Math.floor(count[i] / 2));
    }
    return half + middle + half.split('').reverse().join('');
};