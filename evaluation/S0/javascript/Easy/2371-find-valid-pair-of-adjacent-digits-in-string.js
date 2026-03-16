// Source: https://leetcode.com/problems/find-valid-pair-of-adjacent-digits-in-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting only of digits. A valid pair is defined as two adjacent digits in s such that:
//
//
// 	The first digit is not equal to the second.
// 	Each digit in the pair appears in s exactly as many times as its numeric value.
//
//
// Return the first valid pair found in the string s when traversing from left to right. If no valid pair exists, return an empty string.
//
// Example:
// Input: s = "2523533"
//
// Output: "23"
//
// Explanation:
//
// Digit '2' appears 2 times and digit '3' appears 3 times. Each digit in the pair "23" appears in s exactly as many times as its numeric value. Hence, the output is "23".
//
// Constraints:
// 2 <= s.length <= 100
// 	s only consists of digits from '1' to '9'.
//

/**
 * @param {string} s
 * @return {string}
 */
var findValidPair = function(s) {
    const freq = Array(10).fill(0);
    for (const char of s) {
        freq[parseInt(char)]++;
    }
    for (let i = 0; i < s.length - 1; i++) {    
        const firstDigit = parseInt(s[i]);
        const secondDigit = parseInt(s[i + 1]);
        if (firstDigit !== secondDigit && freq[firstDigit] === firstDigit && freq[secondDigit] === secondDigit) {
            return s.substring(i, i + 2);
        }
    }
    return "";  
};
