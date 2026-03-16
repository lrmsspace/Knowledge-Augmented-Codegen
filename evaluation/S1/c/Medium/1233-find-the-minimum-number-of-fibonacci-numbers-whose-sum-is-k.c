// Source: https://leetcode.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer k, return the minimum number of Fibonacci numbers whose sum is equal to k. The same Fibonacci number can be used multiple times.
//
// The Fibonacci numbers are defined as:
//
//
// 	F1 = 1
// 	F2 = 1
// 	Fn = Fn-1 + Fn-2 for n > 2.
//
// It is guaranteed that for the given constraints we can always find such Fibonacci numbers that sum up to k.
//
// Example:
// Input: k = 7
// Output: 2 
// Explanation: The Fibonacci numbers are: 1, 1, 2, 3, 5, 8, 13, ... 
// For k = 7 we can use 2 + 5 = 7.
//
// Constraints:
// 1 <= k <= 109
//
// Helpful references (internal KB):
// - Fibonacci Numbers (array, dp-1d)
//   • When to use: Use this when calculating the n-th Fibonacci number or similar sequences where each term depends on a fixed number of preceding terms. It efficiently avoids redundant computations for moderate 'n' values.
//   • Idea: This algorithm calculates Fibonacci numbers iteratively by storing previously computed values in an array, building up to the desired n-th term. This approach achieves O(N) time complexity and O(N) space complexity.
//   • Invariants: dp[i] correctly stores the i-th Fibonacci number.; For i >= 2, dp[i] is computed as the sum of dp[i-1] and dp[i-2].
//   • Tips: Initialize base cases (F0, F1) correctly to start the sequence.; Use an array or two variables to store only the necessary previous terms.
//   • Pitfalls: Incorrectly initializing the base cases can lead to wrong results.; A naive recursive solution without memoization will lead to exponential time complexity.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findMinFibonacciNumbers(int k) {
    // Generate Fibonacci numbers up to k
    int fib[44]; // 44th Fibonacci number is 701408733, which is less than 10^9
    fib[0] = 1;
    fib[1] = 1;
    int count = 2;
    while (1) {
        int next_fib = fib[count - 1] + fib[count - 2];
        if (next_fib > k) {
            break;
        }
        fib[count++] = next_fib;
    }

    // Greedily subtract the largest Fibonacci numbers from k
    int result = 0;
    for (int i = count - 1; i >= 0 && k > 0; i--) {
        if (fib[i] <= k) {
            k -= fib[i];
            result++;
        }
    }

    return result;      
}
