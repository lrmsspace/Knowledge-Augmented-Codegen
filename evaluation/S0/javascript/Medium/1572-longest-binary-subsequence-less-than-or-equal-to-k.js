// Source: https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s and a positive integer k.
//
// Return the length of the longest subsequence of s that makes up a binary number less than or equal to k.
//
// Note:
//
//
// 	The subsequence can contain leading zeroes.
// 	The empty string is considered to be equal to 0.
// 	A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
//
// Example:
// Input: s = "1001010", k = 5
// Output: 5
// Explanation: The longest subsequence of s that makes up a binary number less than or equal to 5 is "00010", as this number is equal to 2 in decimal.
// Note that "00100" and "00101" are also possible, which are equal to 4 and 5 in decimal, respectively.
// The length of this subsequence is 5, so 5 is returned.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
// 	1 <= k <= 109
//

/**
 * @param {string} s
 * @param {number} k
 * @return {number}
 */
var longestSubsequence = function(s, k) {
    let countZeros = 0;
    for (const char of s) {
        if (char === '0') {
            countZeros++;
        }
    }
    let countOnes = 0;
    let value = 0;
    for (let i = s.length - 1; i >= 0; i--) {
        const bit = s[i] === '1' ? 1 : 0;
        if (bit === 1) {
            const newValue = value + (1 << countOnes);
            if (newValue <= k) {
                value = newValue;
                countOnes++;
            }
        } else {
            countOnes++;
        }
    }
    return countZeros + countOnes;
};