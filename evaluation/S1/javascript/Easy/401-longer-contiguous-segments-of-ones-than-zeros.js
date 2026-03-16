// Source: https://leetcode.com/problems/longer-contiguous-segments-of-ones-than-zeros/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary string s, return true if the longest contiguous segment of 1's is strictly longer than the longest contiguous segment of 0's in s, or return false otherwise.
//
//
// 	For example, in s = "110100010" the longest continuous segment of 1s has length 2, and the longest continuous segment of 0s has length 3.
//
//
// Note that if there are no 0's, then the longest continuous segment of 0's is considered to have a length 0. The same applies if there is no 1's.
//
// Example:
// Input: s = "1101"
// Output: true
// Explanation:
// The longest contiguous segment of 1s has length 2: "1101"
// The longest contiguous segment of 0s has length 1: "1101"
// The segment of 1s is longer, so return true.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i] is either '0' or '1'.
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
 * @return {boolean}
 */
var checkZeroOnes = function(s) {
    let maxOnes = 0;
    let maxZeros = 0;
    let currentCount = 1;
    for (let i = 1; i < s.length; i++) {
        if (s[i] === s[i - 1]) {
            currentCount++;
        } else {
            if (s[i - 1] === '1') {
                maxOnes = Math.max(maxOnes, currentCount);
            } else {
                maxZeros = Math.max(maxZeros, currentCount);
            }
            currentCount = 1;
        }
    }
    if (s[s.length - 1] === '1') {
        maxOnes = Math.max(maxOnes, currentCount);
    } else {
        maxZeros = Math.max(maxZeros, currentCount);
    }
    return maxOnes > maxZeros;
};