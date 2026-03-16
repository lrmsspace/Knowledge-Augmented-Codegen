// Source: https://leetcode.com/problems/count-substrings-divisible-by-last-digit/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of digits.
//
// Return the number of substrings of s divisible by their non-zero last digit.
//
// Note: A substring may contain leading zeros.
//
// Example:
// Input: s = "12936"
//
// Output: 11
//
// Explanation:
//
// Substrings "29", "129", "293" and "2936" are not divisible by their last digit. There are 15 substrings in total, so the answer is 15 - 4 = 11.
//
// Constraints:
// 1 <= s.length <= 105
//  s consists of digits only.
//

/**
 * @param {string} s
 * @return {number}
 */
var countSubstrings = function(s) {
    let count = 0;
    const n = s.length;
    for (let i = 0; i < n; i++) {
        let num = 0;
        for (let j = i; j < n; j++) {
            num = (num * 10 + (s[j].charCodeAt(0) - '0'.charCodeAt(0))) % 10;
            const lastDigit = s[j] === '0' ? 0 : (s[j].charCodeAt(0) - '0'.charCodeAt(0));
            if (lastDigit !== 0 && num % lastDigit === 0) {
                count++;
            }                                   
        }
    }
    return count;   
};
