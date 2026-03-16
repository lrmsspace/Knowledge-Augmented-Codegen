// Source: https://leetcode.com/problems/backspace-string-compare/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.
//
// Note that after backspacing an empty text, the text will continue empty.
//
// Example:
// Input: s = "ab#c", t = "ad#c"
// Output: true
// Explanation: Both s and t become "ac".
//
// Constraints:
// 1 <= s.length, t.length <= 200
// 	s and t only contain lowercase letters and '#' characters.
//
//
//  
// Follow up: Can you solve it in O(n) time and O(1) space?
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
 * @param {string} t
 * @return {boolean}
 */
var backspaceCompare = function(s, t) {
    const processString = (str) => {
        const stack = [];
        for (const char of str) {
            if (char === '#') {
                if (stack.length > 0) {
                    stack.pop();
                }
            } else {
                stack.push(char);
            }
        }
        return stack.join('');
    };
    
    return processString(s) === processString(t);
};
