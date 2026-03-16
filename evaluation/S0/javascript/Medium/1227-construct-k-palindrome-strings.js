// Source: https://leetcode.com/problems/construct-k-palindrome-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return true if you can use all the characters in s to construct non-empty k palindrome strings or false otherwise.
//
// Example:
// Input: s = "annabelle", k = 2
// Output: true
// Explanation: You can construct two palindromes using all characters in s.
// Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	1 <= k <= 105
//

/**
 * @param {string} s
 * @param {number} k
 * @return {boolean}
 */
var canConstruct = function(s, k) {
    if (s.length < k) return false;
    const charCount = new Array(26).fill(0);
    for (let char of s) {
        charCount[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }
    let oddCount = 0;
    for (let count of charCount) {
        if (count % 2 !== 0) oddCount++;
    }
    return oddCount <= k;
        
};
