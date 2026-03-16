// Source: https://leetcode.com/problems/count-number-of-homogenous-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the number of homogenous substrings of s. Since the answer may be too large, return it modulo 109 + 7.
//
// A string is homogenous if all the characters of the string are the same.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "abbcccaa"
// Output: 13
// Explanation: The homogenous substrings are listed as below:
// "a"   appears 3 times.
// "aa"  appears 1 time.
// "b"   appears 2 times.
// "bb"  appears 1 time.
// "c"   appears 3 times.
// "cc"  appears 2 times.
// "ccc" appears 1 time.
// 3 + 1 + 2 + 1 + 3 + 2 + 1 = 13.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase letters.
//

/**
 * @param {string} s
 * @return {number}
 */
var countHomogenous = function(s) {
    const MOD = 1e9 + 7;
    let count = 0;
    let length = 1;
    for (let i = 1; i <= s.length; i++) {
        if (i < s.length && s[i] === s[i - 1]) {
            length++;
        } else {
            count += (length * (length + 1)) / 2;
            count %= MOD;
            length = 1;
        }
    }
    return count;
};