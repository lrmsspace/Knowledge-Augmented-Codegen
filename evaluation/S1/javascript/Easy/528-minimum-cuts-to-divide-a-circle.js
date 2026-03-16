// Source: https://leetcode.com/problems/minimum-cuts-to-divide-a-circle/   |   Difficulty: Easy
//
// Problem Description:
// A valid cut in a circle can be:
//
//
// 	A cut that is represented by a straight line that touches two points on the edge of the circle and passes through its center, or
// 	A cut that is represented by a straight line that touches one point on the edge of the circle and its center.
//
//
// Some valid and invalid cuts are shown in the figures below.
//
// Given the integer n, return the minimum number of cuts needed to divide a circle into n equal slices.
//
// Example:
// Input: n = 4
// Output: 2
// Explanation: 
// The above figure shows how cutting the circle twice through the middle divides it into 4 equal slices.
//
// Constraints:
// 1 <= n <= 100
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
 * @return {number}
 */
var numberOfCuts = function(n) {
    if (n === 1) return 0;
    return n % 2 === 0 ? n / 2 : n;
};
