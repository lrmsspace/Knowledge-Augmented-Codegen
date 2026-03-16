// Source: https://leetcode.com/problems/find-special-substring-of-length-k/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s and an integer k.
//
// Determine if there exists a substring of length exactly k in s that satisfies the following conditions:
//
//
// 	The substring consists of only one distinct character (e.g., "aaa" or "bbb").
// 	If there is a character immediately before the substring, it must be different from the character in the substring.
// 	If there is a character immediately after the substring, it must also be different from the character in the substring.
//
//
// Return true if such a substring exists. Otherwise, return false.
//
// Example:
// Input: s = "aaabaaa", k = 3
//
// Output: true
//
// Explanation:
//
// The substring s[4..6] == "aaa" satisfies the conditions.
//
//
// 	It has a length of 3.
// 	All characters are the same.
// 	The character before "aaa" is 'b', which is different from 'a'.
// 	There is no character after "aaa".
//
// Constraints:
// 1 <= k <= s.length <= 100
// 	s consists of lowercase English letters only.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {boolean}
 */
var hasSpecialSubstring = function(s, k) {
    for (let i = 0; i <= s.length - k; i++) {
        const substring = s.slice(i, i + k);
        const distinctChars = new Set(substring);
        if (distinctChars.size === 1) {
            const char = substring[0];
            const beforeChar = i > 0 ? s[i - 1] : null;
            const afterChar = i + k < s.length ? s[i + k] : null;
            if (beforeChar !== char && afterChar !== char) {
                return true;
            }
        }
    }
    return false;
};