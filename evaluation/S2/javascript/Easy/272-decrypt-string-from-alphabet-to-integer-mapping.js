// Source: https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s formed by digits and '#'. We want to map s to English lowercase characters as follows:
//
//
// 	Characters ('a' to 'i') are represented by ('1' to '9') respectively.
// 	Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.
//
//
// Return the string formed after mapping.
//
// The test cases are generated so that a unique mapping will always exist.
//
// Example:
// Input: s = "10#11#12"
// Output: "jkab"
// Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of digits and the '#' letter.
// 	s will be a valid string such that mapping is always possible.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {string}
 */
var freqAlphabets = function(s) {
    let result = '';
    let i = s.length - 1;
    
    while (i >= 0) {
        if (s[i] === '#') {
            const num = parseInt(s.substring(i - 2, i), 10);
            result = String.fromCharCode(num + 96) + result;
            i -= 3;
        } else {
            const num = parseInt(s[i], 10);
            result = String.fromCharCode(num + 96) + result;
            i -= 1;
        }
    }
    
    return result;
};
