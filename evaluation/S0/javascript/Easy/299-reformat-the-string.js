// Source: https://leetcode.com/problems/reformat-the-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given an alphanumeric string s. (Alphanumeric string is a string consisting of lowercase English letters and digits).
//
// You have to find a permutation of the string where no letter is followed by another letter and no digit is followed by another digit. That is, no two adjacent characters have the same type.
//
// Return the reformatted string or return an empty string if it is impossible to reformat the string.
//
// Example:
// Input: s = "a0b1c2"
// Output: "0a1b2c"
// Explanation: No two adjacent characters have the same type in "0a1b2c". "a0b1c2", "0a1b2c", "0c2a1b" are also valid permutations.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters and/or digits.
//

/**
 * @param {string} s
 * @return {string}
 */
var reformat = function(s) {
    const letters = [];
    const digits = [];
    for (const char of s) {
        if (char >= '0' && char <= '9') {
            digits.push(char);
        } else {
            letters.push(char);
        }
    }
    if (Math.abs(letters.length - digits.length) > 1) {
        return "";
    }
    const result = [];
    let i = 0, j = 0;
    const useLetterFirst = letters.length >= digits.length;
    while (i < letters.length || j < digits.length) {
        if (useLetterFirst) {
            if (i < letters.length) {
                result.push(letters[i++]);
            }
            if (j < digits.length) {
                result.push(digits[j++]);
            }
        } else {
            if (j < digits.length) {
                result.push(digits[j++]);
            }
            if (i < letters.length) {
                result.push(letters[i++]);
            }
        }
    }
    return result.join('');
};