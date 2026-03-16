// Source: https://leetcode.com/problems/inverse-coin-change/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 1-indexed integer array numWays, where numWays[i] represents the number of ways to select a total amount i using an infinite supply of some fixed coin denominations. Each denomination is a positive integer with value at most numWays.length.
//
// However, the exact coin denominations have been lost. Your task is to recover the set of denominations that could have resulted in the given numWays array.
//
// Return a sorted array containing unique integers which represents this set of denominations.
//
// If no such set exists, return an empty array.
//
// Example:
// Input: numWays = [0,1,0,2,0,3,0,4,0,5]
//
// Output: [2,4,6]
//
// Explanation:
//
//
// 	
// 		
// 			Amount
// 			Number of ways
// 			Explanation
// 		
// 		
// 			1
// 			0
// 			There is no way to select coins with total value 1.
// 		
// 		
// 			2
// 			1
// 			The only way is [2].
// 		
// 		
// 			3
// 			0
// 			There is no way to select coins with total value 3.
// 		
// 		
// 			4
// 			2
// 			The ways are [2, 2] and [4].
// 		
// 		
// 			5
// 			0
// 			There is no way to select coins with total value 5.
// 		
// 		
// 			6
// 			3
// 			The ways are [2, 2, 2], [2, 4], and [6].
// 		
// 		
// 			7
// 			0
// 			There is no way to select coins with total value 7.
// 		
// 		
// 			8
// 			4
// 			The ways are [2, 2, 2, 2], [2, 2, 4], [2, 6], and [4, 4].
// 		
// 		
// 			9
// 			0
// 			There is no way to select coins with total value 9.
// 		
// 		
// 			10
// 			5
// 			The ways are [2, 2, 2, 2, 2], [2, 2, 2, 4], [2, 4, 4], [2, 2, 6], and [4, 6].
//
// Constraints:
// 1 <= numWays.length <= 100
// 	0 <= numWays[i] <= 2 * 108
//
// Helpful references (internal KB):
// - Fibonacci Numbers (array, dp-1d)
//   • When to use: Use this when calculating the n-th Fibonacci number or similar sequences where each term depends on a fixed number of preceding terms. It efficiently avoids redundant computations for moderate 'n' values.
//   • Idea: This algorithm calculates Fibonacci numbers iteratively by storing previously computed values in an array, building up to the desired n-th term. This approach achieves O(N) time complexity and O(N) space complexity.
//   • Invariants: dp[i] correctly stores the i-th Fibonacci number.; For i >= 2, dp[i] is computed as the sum of dp[i-1] and dp[i-2].
//   • Tips: Initialize base cases (F0, F1) correctly to start the sequence.; Use an array or two variables to store only the necessary previous terms.
//   • Pitfalls: Incorrectly initializing the base cases can lead to wrong results.; A naive recursive solution without memoization will lead to exponential time complexity.
// - Binomial Coefficients (array, dp-2d)
//   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
//   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
//   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
//   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
//   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
// - Modular Multiplicative Inverse (array, number, dp-1d)
//   • When to use: Use when division operations are required in modular arithmetic, especially for combinatorics or probability problems under a modulus. It's crucial for precomputing inverses efficiently for a range of numbers.
//   • Idea: Calculates the modular multiplicative inverse of a number 'a' modulo 'm', which is an integer 'x' such that (a * x) % m == 1. When precomputing inverses for a range [1, N], a linear time O(N) dynamic programming approach can be used.
//   • Invariants: For all k in [1, i-1], inv[k] correctly stores k^(-1) % m.; inv[i] is computed using previously calculated inv[m % i].
//   • Tips: For prime modulus 'm', a^(m-2) % m (Fermat's Little Theorem) is efficient for a single inverse.; The Extended Euclidean Algorithm works for any 'm' if gcd(a, m) = 1.
//   • Pitfalls: A modular inverse only exists if gcd(a, m) == 1.; Fermat's Little Theorem is only applicable when the modulus 'm' is prime.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} numWays
 * @return {number[]}
 */
var findCoins = function(numWays) {
    const denominations = [];
    let prev = 1; // Start with the base case for amount 0
    for (let i = 1; i < numWays.length; i++) {
        if (numWays[i] > prev) {
            const coin = i - denominations.reduce((sum, d) => sum + d, 0);
            denominations.push(coin);
        }
        prev = numWays[i];
    }
    return denominations;
};
