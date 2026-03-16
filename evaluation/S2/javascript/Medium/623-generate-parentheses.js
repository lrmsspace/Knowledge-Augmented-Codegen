// Source: https://leetcode.com/problems/generate-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
//
// Example:
// Input: n = 3
// Output: ["((()))","(()())","(())()","()(())","()()()"]
//
// Constraints:
// 1 <= n <= 8
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
 * @param {number} n
 * @return {string[]}
 */
var generateParenthesis = function(n) {
    const res = [];
    const backtrack = (s, left, right) => {
        if (s.length === 2 * n) {
            res.push(s);
            return;
        }
        if (left < n) backtrack(s + '(', left + 1, right);
        if (right < left) backtrack(s + ')', left, right + 1);
    };
    backtrack('', 0, 0);
    return res;
};
