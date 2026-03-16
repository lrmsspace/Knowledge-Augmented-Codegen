// Source: https://leetcode.com/problems/goal-parser-interpretation/   |   Difficulty: Easy
//
// Problem Description:
// You own a Goal Parser that can interpret a string command. The command consists of an alphabet of "G", "()" and/or "(al)" in some order. The Goal Parser will interpret "G" as the string "G", "()" as the string "o", and "(al)" as the string "al". The interpreted strings are then concatenated in the original order.
//
// Given the string command, return the Goal Parser's interpretation of command.
//
// Example:
// Input: command = "G()(al)"
// Output: "Goal"
// Explanation: The Goal Parser interprets the command as follows:
// G -> G
// () -> o
// (al) -> al
// The final concatenated result is "Goal".
//
// Constraints:
// 1 <= command.length <= 100
// 	command consists of "G", "()", and/or "(al)" in some order.
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
 * @param {string} command
 * @return {string}
 */
var interpret = function(command) {
    let result = '';
    for (let i = 0; i < command.length; i++) {
        if (command[i] === 'G') {
            result += 'G';
        } else if (command[i] === '(' && command[i + 1] === ')') {
            result += 'o';
            i++; // Skip the next character since it's part of the pattern "()"
        } else if (command[i] === '(' && command[i + 1] === 'a' && command[i + 2] === 'l' && command[i + 3] === ')') {
            result += 'al';
            i += 3; // Skip the next three characters since they're part of the pattern "(al)"
        }
    }
    return result;
};