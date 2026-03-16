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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int makeTheIntegerZero(int num1, int num2) {
    int operations = 0;

    while (num1 > 0) {
        if (num1 < num2) {
            return -1;
        }
        num1 -= num2;
        operations++;

        // Count the number of set bits in num1
        int setBits = 0;
        int temp = num1;
        while (temp > 0) {
            setBits += temp & 1;
            temp >>= 1;
        }

        // If the number of set bits exceeds the number of operations, it's impossible
        if (setBits > operations) {
            return -1;
        }
    }

    return operations;      
}
