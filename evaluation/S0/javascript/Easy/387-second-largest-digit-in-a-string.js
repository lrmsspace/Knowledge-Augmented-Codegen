// Source: https://leetcode.com/problems/second-largest-digit-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given an alphanumeric string s, return the second largest numerical digit that appears in s, or -1 if it does not exist.
//
// An alphanumeric string is a string consisting of lowercase English letters and digits.
//
// Example:
// Input: s = "dfa12321afd"
// Output: 2
// Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters and digits.
//

/**
 * @param {string} s
 * @return {number}
 */
var secondHighest = function(s) {
    const digits = new Set();
    for (const char of s) {
        if (char >= '0' && char <= '9') {
            digits.add(parseInt(char));
        }
    }
    const uniqueDigits = Array.from(digits).sort((a, b) => b - a);
    return uniqueDigits.length < 2 ? -1 : uniqueDigits[1];
};
