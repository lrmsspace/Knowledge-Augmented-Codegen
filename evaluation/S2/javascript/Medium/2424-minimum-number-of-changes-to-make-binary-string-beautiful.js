// Source: https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed binary string s having an even length.
//
// A string is beautiful if it's possible to partition it into one or more substrings such that:
//
//
// 	Each substring has an even length.
// 	Each substring contains only 1's or only 0's.
//
//
// You can change any character in s to 0 or 1.
//
// Return the minimum number of changes required to make the string s beautiful.
//
// Example:
// Input: s = "1001"
// Output: 2
// Explanation: We change s[1] to 1 and s[3] to 0 to get string "1100".
// It can be seen that the string "1100" is beautiful because we can partition it into "11|00".
// It can be proven that 2 is the minimum number of changes needed to make the string beautiful.
//
// Constraints:
// 2 <= s.length <= 105
// 	s has an even length.
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
 * @return {number}
 */
var minChanges = function(s) {
    let changesForZero = 0;
    let changesForOne = 0;
    
    for (let i = 0; i < s.length; i++) {
        if (i % 2 === 0) {
            if (s[i] !== '0') changesForZero++;
            if (s[i] !== '1') changesForOne++;
        } else {
            if (s[i] !== '1') changesForZero++;
            if (s[i] !== '0') changesForOne++;
        }
    }
    
    return Math.min(changesForZero, changesForOne);
};
