// Source: https://leetcode.com/problems/fibonacci-number/   |   Difficulty: Easy
//
// Problem Description:
// The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,
//
//
// F(0) = 0, F(1) = 1
// F(n) = F(n - 1) + F(n - 2), for n > 1.
//
//
// Given n, calculate F(n).
//
// Example:
// Input: n = 2
// Output: 1
// Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
//
// Constraints:
// 0 <= n <= 30
//
// Helpful references (internal KB):
// - Fibonacci Numbers (array, dp-1d)
//   • When to use: Use this when calculating the n-th Fibonacci number or similar sequences where each term depends on a fixed number of preceding terms. It efficiently avoids redundant computations for moderate 'n' values.
//   • Idea: This algorithm calculates Fibonacci numbers iteratively by storing previously computed values in an array, building up to the desired n-th term. This approach achieves O(N) time complexity and O(N) space complexity.
//   • Invariants: dp[i] correctly stores the i-th Fibonacci number.; For i >= 2, dp[i] is computed as the sum of dp[i-1] and dp[i-2].
//   • Tips: Initialize base cases (F0, F1) correctly to start the sequence.; Use an array or two variables to store only the necessary previous terms.
//   • Pitfalls: Incorrectly initializing the base cases can lead to wrong results.; A naive recursive solution without memoization will lead to exponential time complexity.
// - Fibonacci Numbers (matrix, matrix-exp)
//   • When to use: Use when needing to compute the N-th Fibonacci number or similar linear recurrence relations for very large N efficiently, typically in logarithmic time.
//   • Idea: This method computes the N-th Fibonacci number by transforming the linear recurrence into a matrix multiplication, then using binary exponentiation (matrix exponentiation) to raise the transformation matrix to the N-th power. It achieves O(log N) time complexity.
//   • Invariants: The base matrix M = [[1, 1], [1, 0]] correctly transforms (F_k, F_{k-1}) to (F_{k+1}, F_k).; After k matrix multiplications, the accumulated matrix represents M^k.
//   • Tips: Understand binary exponentiation for matrices to efficiently compute powers.; The base transformation matrix for Fibonacci is typically [[1, 1], [1, 0]].
//   • Pitfalls: Incorrectly setting up the base matrix or initial vector.; Forgetting to apply modulo operations, leading to integer overflow for large numbers.
// - Fibonacci Numbers (number, recursion, binary-lifting)
//   • When to use: Use when computing the N-th Fibonacci number for extremely large N, or when the result needs to be calculated modulo a specific value, requiring logarithmic time complexity.
//   • Idea: This method computes the N-th Fibonacci number by leveraging matrix exponentiation or specific doubling identities, reducing the problem size by half in each step. It achieves an O(log N) time complexity.
//   • Invariants: The function `compute(n)` always returns the pair `(F_n, F_{n+1})`.; For any `k`, the values `F_k` and `F_{k+1}` are correctly computed before deriving `F_{2k}` and `F_{2k+1}`.
//   • Tips: Utilize matrix exponentiation for a general and robust approach.; The doubling identities F_2k+1 and F_2k can be faster than explicit matrix multiplication.
//   • Pitfalls: Integer overflow if modulo arithmetic or arbitrary-precision integers are not used for large N.; Incorrectly defining base cases in the recursive implementation can lead to errors.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int fib(int n) {
        if (n <= 1) {
            return n;
        }
        int[] dp = new int[n + 1];
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];           
    }
}
