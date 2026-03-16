// Source: https://leetcode.com/problems/count-square-sum-triples/   |   Difficulty: Easy
//
// Problem Description:
// A square triple (a,b,c) is a triple where a, b, and c are integers and a2 + b2 = c2.
//
// Given an integer n, return the number of square triples such that 1 <= a, b, c <= n.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: The square triples are (3,4,5) and (4,3,5).
//
// Constraints:
// 1 <= n <= 250
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
// - Finding common tangents to two circles (geometry, number, enumeration, simulation)
//   • When to use: Use this when you need to find all lines that are simultaneously tangent to two given circles. It is applicable in computational geometry problems requiring the precise relative positioning of circles and lines.
//   • Idea: This algorithm systematically determines the equations of all common tangent lines to two circles, typically identifying up to four distinct lines. It involves geometric calculations based on circle centers and radii, operating in constant time, O(1).
//   • Invariants: The distance between the two circle centers remains constant.; The radii of both circles are immutable during the tangent calculation.
//   • Tips: Separate calculations for external and internal tangents.; Carefully consider the relative positions of circle centers and radii.
//   • Pitfalls: Overlooking degenerate cases like coincident or concentric circles.; Numerical instability or precision errors with floating-point arithmetic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countTriples(int n) {
    int count = 0;
    for (int a = 1; a <= n; a++) {
        for (int b = 1; b <= n; b++) {
            int c2 = a * a + b * b;
            int c = (int)sqrt(c2);
            if (c * c == c2 && c <= n) {
                count++;
            }
        }
    }
    return count;       
}
