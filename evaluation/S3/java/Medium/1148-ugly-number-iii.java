// Source: https://leetcode.com/problems/ugly-number-iii/   |   Difficulty: Medium
//
// Problem Description:
// An ugly number is a positive integer that is divisible by a, b, or c.
//
// Given four integers n, a, b, and c, return the nth ugly number.
//
// Example:
// Input: n = 3, a = 2, b = 3, c = 5
// Output: 4
// Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.
//
// Constraints:
// 1 <= n, a, b, c <= 109
// 	1 <= a * b * c <= 1018
// 	It is guaranteed that the result will be in range [1, 2 * 109].
//
// Helpful references (internal KB):
// - Finding the equation of a line for a segment (number, geometry, gcd)
//   • When to use: Use this method when you need to represent a line segment's equation using integer coefficients, especially to avoid floating-point inaccuracies in geometric computations.
//   • Idea: This method derives the general form of a line equation (Ax + By + C = 0) from two points, ensuring integer coefficients if input coordinates are integers. It then normalizes these coefficients using GCD to achieve a unique representation, typically in O(log(max(|A|,|B|,|C|))) time due to GCD.
//   • Invariants: The calculated coefficients A, B, C always satisfy A*Px + B*Py + C = 0 for point P(Px, Py).; After GCD division, the absolute values of A, B, C are coprime (unless all are zero).
//   • Tips: Always compute A, B, C using the given formulas for P(Px, Py) and Q(Qx, Qy).; Use absolute values of A, B, C when calculating their greatest common divisor.
//   • Pitfalls: Forgetting to normalize coefficients leads to non-unique representations for the same line.; Incorrectly handling signs during the final normalization step can result in inconsistent forms.
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two or more integers, or as a subroutine for tasks like simplifying fractions or finding the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the division algorithm. It operates in logarithmic time complexity, O(log min(a, b)).
//   • Invariants: The greatest common divisor of the current pair (a, b) remains constant and equal to the GCD of the original inputs.; The second number (b) is always non-negative.
//   • Tips: Handle the base case where one of the numbers is zero; gcd(a, 0) = a.; The algorithm works for any order of inputs; if a < b, the first step swaps them effectively.
//   • Pitfalls: Forgetting to take absolute values if negative inputs are possible, as GCD is typically defined for non-negative integers.; Incorrectly handling the zero input case, which can lead to infinite loops or incorrect results.
// - Arbitrary-Precision Arithmetic (number, gcd)
//   • When to use: When standard integer types cannot hold the magnitude of numbers required for calculations, or when exact results for very large numbers are necessary.
//   • Idea: A technique to represent and operate on integers of arbitrary size, exceeding built-in data type limits, often by storing numbers as sequences of digits or in modular form. Operations are implemented manually, typically with complexity proportional to the number of digits.
//   • Invariants: The stored representation accurately reflects the numerical value.; Each digit or modular component is within its valid range for the chosen base/modulus.
//   • Tips: Choose a suitable base for digit representation (e.g., powers of 10 or 2^k) to balance memory and computation.; Implement basic arithmetic operations (add, subtract, multiply, divide) carefully, handling carries/borrows.
//   • Pitfalls: Inefficient implementation of basic operations can lead to Time Limit Exceeded for large inputs.; Off-by-one errors or incorrect carry/borrow handling are common during manual arithmetic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int nthUglyNumber(int n, int a, int b, int c) {
        long l = 1, r = 2000000000;
        long ab = lcm(a, b), ac = lcm(a, c), bc = lcm(b, c);
        long abc = lcm(ab, c);

        while (l < r) {
            long m = l + (r - l) / 2;
            long count = m / a + m / b + m / c - m / ab - m / ac - m / bc + m / abc;

            if (count < n) {
                l = m + 1;
            } else {
                r = m;
            }
        }

        return (int) l;         
    }
}
