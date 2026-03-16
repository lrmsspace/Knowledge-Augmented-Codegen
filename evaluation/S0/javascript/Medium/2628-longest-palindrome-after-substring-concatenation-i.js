// Source: https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings, s and t.
//
// You can create a new string by selecting a substring from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.
//
// Return the length of the longest palindrome that can be formed this way.
//
// Example:
// Input: s = "a", t = "a"
//
// Output: 2
//
// Explanation:
//
// Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.
//
// Constraints:
// 1 <= s.length, t.length <= 30
// 	s and t consist of lowercase English letters.
//

/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var longestPalindrome = function(s, t) {
    const countS = new Array(26).fill(0);
    const countT = new Array(26).fill(0);
    for (const char of s) {
        countS[char.charCodeAt(0) - 97]++;
    }
    for (const char of t) {
        countT[char.charCodeAt(0) - 97]++;
    }
    let maxLength = 0;
    for (let i = 0; i < 26; i++) {
        maxLength += 2 * Math.min(countS[i], countT[i]);
    }
    for (let i = 0; i < 26; i++) {
        if (countS[i] > 0 && countT[i] > 0) {
            maxLength++;
            break;
        }
    }
    return maxLength;
};