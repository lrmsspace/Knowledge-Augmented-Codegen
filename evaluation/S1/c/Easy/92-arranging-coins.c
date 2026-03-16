// Source: https://leetcode.com/problems/arranging-coins/   |   Difficulty: Easy
//
// Problem Description:
// You have n coins and you want to build a staircase with these coins. The staircase consists of k rows where the ith row has exactly i coins. The last row of the staircase may be incomplete.
//
// Given the integer n, return the number of complete rows of the staircase you will build.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: Because the 3rd row is incomplete, we return 2.
//
// Constraints:
// 1 <= n <= 231 - 1
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Stars and bars (number, counting)
//   • When to use: When counting the number of ways to distribute 'n' identical items into 'k' distinct containers, or finding the number of non-negative integer solutions to an equation x1 + ... + xk = n.
//   • Idea: A combinatorial technique to count arrangements of identical items into distinct bins, or non-negative integer solutions to a sum, by modeling them as permutations of 'n' stars and 'k-1' bars. It typically has a time complexity of O(1) after binomial coefficient precomputation, or O(min(n, k)) for direct calculation.
//   • Invariants: The total number of stars remains 'n' throughout the arrangement.; The total number of bars remains 'k-1' throughout the arrangement.
//   • Tips: Clearly identify 'n' (identical objects) and 'k' (distinct bins/variables).; Remember the formula: C(n + k - 1, k - 1) or C(n + k - 1, n).
//   • Pitfalls: Confusing identical objects with distinct objects.; Incorrectly identifying 'n' or 'k' in the problem statement.
// - Continued fractions (tree, number, binary-search, enumeration)
//   • When to use: Use when seeking the best rational approximations for real numbers or when analyzing properties of numbers related to their fractional parts. It is also applicable for solving certain linear Diophantine equations.
//   • Idea: Continued fractions represent a real number as a sequence of integers, providing a series of increasingly accurate rational approximations called convergents. The process is analogous to the Euclidean algorithm, typically having logarithmic complexity relative to the magnitude of the number's denominator.
//   • Invariants: The current remainder in the iterative process is always positive and less than 1.; Each successive convergent p_k/q_k has a denominator q_k that is strictly increasing.
//   • Tips: Understand the connection between continued fractions and the Euclidean algorithm for rational numbers.; Convergents provide the 'best' rational approximations for a given denominator size.
//   • Pitfalls: Numerical precision issues can arise when computing continued fractions for floating-point numbers.; Misinterpreting the 'best approximation' property; it's specific to denominator size.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int arrangeCoins(int n) {
    long left = 0, right = n;
    while (left < right) {
        long mid = left + (right - left + 1) / 2;
        long curr = mid * (mid + 1) / 2;
        if (curr <= n) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    return (int)left;       
}
