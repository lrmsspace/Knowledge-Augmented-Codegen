// Source: https://leetcode.com/problems/divide-two-integers/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
//
// The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.
//
// Return the quotient after dividing dividend by divisor.
//
// Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For this problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1, and if the quotient is strictly less than -231, then return -231.
//
// Example:
// Input: dividend = 10, divisor = 3
// Output: 3
// Explanation: 10/3 = 3.33333.. which is truncated to 3.
//
// Constraints:
// -231 <= dividend, divisor <= 231 - 1
// 	divisor != 0
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Arbitrary-Precision Arithmetic (number, gcd)
//   • When to use: When standard integer types cannot hold the magnitude of numbers required for calculations, or when exact results for very large numbers are necessary.
//   • Idea: A technique to represent and operate on integers of arbitrary size, exceeding built-in data type limits, often by storing numbers as sequences of digits or in modular form. Operations are implemented manually, typically with complexity proportional to the number of digits.
//   • Invariants: The stored representation accurately reflects the numerical value.; Each digit or modular component is within its valid range for the chosen base/modulus.
//   • Tips: Choose a suitable base for digit representation (e.g., powers of 10 or 2^k) to balance memory and computation.; Implement basic arithmetic operations (add, subtract, multiply, divide) carefully, handling carries/borrows.
//   • Pitfalls: Inefficient implementation of basic operations can lead to Time Limit Exceeded for large inputs.; Off-by-one errors or incorrect carry/borrow handling are common during manual arithmetic.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int divide(int dividend, int divisor) {
        // Handle overflow case
        if (dividend == Integer.MIN_VALUE && divisor == -1) {
            return Integer.MAX_VALUE;
        }

        // Determine the sign of the result
        boolean negative = (dividend < 0) ^ (divisor < 0);

        // Work with positive values
        long dvd = Math.abs((long) dividend);
        long dvs = Math.abs((long) divisor);
        int result = 0;

        // Subtract divisor multiples from dividend
        while (dvd >= dvs) {
            long temp = dvs, multiple = 1;
            while (dvd >= (temp << 1)) {
                temp <<= 1;
                multiple <<= 1;
            }
            dvd -= temp;
            result += multiple;
        }

        return negative ? -result : result;         
    }
}
