// Source: https://leetcode.com/problems/knight-dialer/   |   Difficulty: Medium
//
// Problem Description:
// The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L). The possible movements of chess knight are shown in this diagram:
//
// A chess knight can move as indicated in the chess diagram below:
//
// We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).
//
// Given an integer n, return how many distinct phone numbers of length n we can dial.
//
// You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.
//
// As the answer may be very large, return the answer modulo 109 + 7.
//
// Example:
// Input: n = 1
// Output: 10
// Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
//
// Constraints:
// 1 <= n <= 5000
//
// Helpful references (internal KB):
// - Josephus Problem (number, dp-1d, recursion)
//   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
//   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
//   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
//   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
//   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Binary Exponentiation (number, mod-exp, divide-and-conquer)
//   • When to use: Use when calculating a^n efficiently, especially for large n or when results need to be taken modulo some number. It reduces the number of multiplications from linear to logarithmic.
//   • Idea: Binary exponentiation computes a^n by repeatedly squaring the base and multiplying terms corresponding to the set bits in the exponent's binary representation. This method achieves a time complexity of O(log n) multiplications.
//   • Invariants: The product of `result` and `current_base` raised to the `remaining_exponent` equals the initial `a^N`.; `current_base` always represents `a` raised to the power of `2^k` for the current iteration `k`.
//   • Tips: Handle base cases like n=0 (result is 1) and n=1 (result is a).; Use long long or appropriate large integer types for intermediate products to prevent overflow.
//   • Pitfalls: Integer overflow if not using appropriate data types or modulo arithmetic.; Incorrectly handling negative exponents (typically not covered by basic binary exponentiation).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int knightDialer(int n) {
        int mod = 1_000_000_007;
        // Mapping of each digit to the digits it can jump to
        int[][] jumps = {
            {4, 6},    // from 0
            {6, 8},    // from 1
            {7, 9},    // from 2
            {4, 8},    // from 3
            {0, 3, 9}, // from 4
            {},       // from 5 (no moves)
            {0, 1, 7}, // from 6
            {2, 6},    // from 7
            {1, 3},    // from 8
            {2, 4}     // from 9
        };

        long[] dp = new long[10];
        Arrays.fill(dp, 1); // Base case: for n=1, each digit can be dialed in one way

        for (int i = 2; i <= n; i++) {
            long[] newDp = new long[10];
            for (int digit = 0; digit <= 9; digit++) {
                for (int next : jumps[digit]) {
                    newDp[next] = (newDp[next] + dp[digit]) % mod;
                }
            }
            dp = newDp;
        }

        long result = 0;
        for (long count : dp) {
            result = (result + count) % mod;
        }
        return (int) result;            
    }
}
