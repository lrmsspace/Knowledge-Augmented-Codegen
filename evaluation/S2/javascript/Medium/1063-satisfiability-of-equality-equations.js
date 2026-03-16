// Source: https://leetcode.com/problems/satisfiability-of-equality-equations/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings equations that represent relationships between variables where each string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.
//
// Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.
//
// Example:
// Input: equations = ["a==b","b!=a"]
// Output: false
// Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
// There is no way to assign the variables to satisfy both equations.
//
// Constraints:
// 1 <= equations.length <= 500
// 	equations[i].length == 4
// 	equations[i][0] is a lowercase letter.
// 	equations[i][1] is either '=' or '!'.
// 	equations[i][2] is '='.
// 	equations[i][3] is a lowercase letter.
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
 * @param {string[]} equations
 * @return {boolean}
 */
var equationsPossible = function(equations) {
    const parent = new Array(26).fill(0).map((_, index) => index);
    const find = (x) => {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    const union = (x, y) => {
        parent[find(x)] = find(y);
    };
    for (const equation of equations) {
        if (equation[1] === '=') {
            union(equation.charCodeAt(0) - 97, equation.charCodeAt(3) - 97);
        }
    }
    for (const equation of equations) {
        if (equation[1] === '!' && find(equation.charCodeAt(0) - 97) === find(equation.charCodeAt(3) - 97)) {
            return false;
        }
    }
    return true;
};
