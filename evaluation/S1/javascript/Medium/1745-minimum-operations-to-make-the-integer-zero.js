// Source: https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers num1 and num2.
//
// In one operation, you can choose integer i in the range [0, 60] and subtract 2i + num2 from num1.
//
// Return the integer denoting the minimum number of operations needed to make num1 equal to 0.
//
// If it is impossible to make num1 equal to 0, return -1.
//
// Example:
// Input: num1 = 3, num2 = -2
// Output: 3
// Explanation: We can make 3 equal to 0 with the following operations:
// - We choose i = 2 and subtract 22 + (-2) from 3, 3 - (4 + (-2)) = 1.
// - We choose i = 2 and subtract 22 + (-2) from 1, 1 - (4 + (-2)) = -1.
// - We choose i = 0 and subtract 20 + (-2) from -1, (-1) - (1 + (-2)) = 0.
// It can be proven, that 3 is the minimum number of operations that we need to perform.
//
// Constraints:
// 1 <= num1 <= 109
//  -109 <= num2 <= 109
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
 * @param {number} num1
 * @param {number} num2
 * @return {number}
 */
var makeTheIntegerZero = function(num1, num2) {
    let operations = 0;

    while (num1 > 0) {
        const powerOfTwo = Math.pow(2, operations);
        const subtractValue = powerOfTwo + num2;

        if (subtractValue > num1) {
            return -1; // If the value to subtract is greater than num1, it's impossible to reach zero
        }

        num1 -= subtractValue;
        operations++;
    }

    return operations;
};
