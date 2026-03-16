// Source: https://leetcode.com/problems/calculate-money-in-leetcode-bank/   |   Difficulty: Easy
//
// Problem Description:
// Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.
//
// He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday, he will put in $1 more than the day before. On every subsequent Monday, he will put in $1 more than the previous Monday. 
//
// Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth day.
//
// Example:
// Input: n = 4
// Output: 10
// Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.
//
// Constraints:
// 1 <= n <= 1000
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
// - Integration by Simpson's formula (number, interval, enumeration, simulation)
//   • When to use: Use when approximating definite integrals of functions that are sufficiently smooth over a given interval. It is effective for achieving good accuracy with a moderate number of subintervals.
//   • Idea: Simpson's formula approximates a definite integral by dividing the integration interval into an even number of subintervals and approximating the function over each pair of subintervals with a parabola. This method offers a higher order of accuracy compared to simpler rules, typically achieving O(N^4) accuracy for N subintervals.
//   • Invariants: The sum accumulates weighted function values for all processed subintervals.; The subinterval width 'h' remains constant across the entire integration range.
//   • Tips: Ensure the total number of subintervals (2n) is always even for the composite rule.; The weights for function evaluations follow a specific 1-4-2-4-...-2-4-1 pattern.
//   • Pitfalls: Incorrectly applying the weighting coefficients, especially at the boundaries or interior points.; Using an odd number of subintervals, which invalidates the parabolic approximation for the composite rule.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int totalMoney(int n) {
    int weeks = n / 7; // Number of complete weeks
    int days = n % 7;  // Remaining days after complete weeks

    // Total money from complete weeks
    int total = weeks * (weeks + 1) / 2 * 7; // Sum of first 'weeks' natural numbers multiplied by 7

    // Add money from the remaining days
    total += days * (weeks + 1) + (days * (days - 1)) / 2; // Money for remaining days

    return total;       
}
