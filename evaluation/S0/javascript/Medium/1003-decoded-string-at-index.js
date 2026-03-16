// Source: https://leetcode.com/problems/decoded-string-at-index/   |   Difficulty: Medium
//
// Problem Description:
// You are given an encoded string s. To decode the string to a tape, the encoded string is read one character at a time and the following steps are taken:
//
//
// 	If the character read is a letter, that letter is written onto the tape.
// 	If the character read is a digit d, the entire current tape is repeatedly written d - 1 more times in total.
//
//
// Given an integer k, return the kth letter (1-indexed) in the decoded string.
//
// Example:
// Input: s = "leet2code3", k = 10
// Output: "o"
// Explanation: The decoded string is "leetleetcodeleetleetcodeleetleetcode".
// The 10th letter in the string is "o".
//
// Constraints:
// 2 <= s.length <= 100
// 	s consists of lowercase English letters and digits 2 through 9.
// 	s starts with a letter.
// 	1 <= k <= 109
// 	It is guaranteed that k is less than or equal to the length of the decoded string.
// 	The decoded string is guaranteed to have less than 263 letters.
//

/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var decodeAtIndex = function(s, k) {
    let size = 0;

    // First, find the size of the decoded string
    for (let char of s) {
        if (isNaN(char)) {
            size += 1;
        } else {
            size *= parseInt(char);
        }
    }    

    // Work backwards to find the kth character
    for (let i = s.length - 1; i >= 0; i--) {
        let char = s[i];
        k %= size;

        if (k === 0 && isNaN(char)) {
            return char;
        }

        if (isNaN(char)) {
            size -= 1;
        } else {
            size /= parseInt(char);
        }
    }
};