// Source: https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones. Otherwise, return false.
//
// Example:
// Input: s = "1001"
// Output: false
// Explanation: The ones do not form a contiguous segment.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i]​​​​ is either '0' or '1'.
// 	s[0] is '1'.
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
var checkOnesSegment = function(s) {
    let foundZero = false;
    for (let i = 0; i < s.length; i++) {
        if (s[i] === '0') {
            foundZero = true;
        } else if (foundZero) {
            // If we find a '1' after we've found a '0', it means there are multiple segments of ones.
            return false;
        }
    }
    return true;
};
