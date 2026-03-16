// Source: https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of digits. Perform the following operation repeatedly until the string has exactly two digits:
//
//
// 	For each pair of consecutive digits in s, starting from the first digit, calculate a new digit as the sum of the two digits modulo 10.
// 	Replace s with the sequence of newly calculated digits, maintaining the order in which they are computed.
//
//
// Return true if the final two digits in s are the same; otherwise, return false.
//
// Example:
// Input: s = "3902"
//
// Output: true
//
// Explanation:
//
//
// 	Initially, s = "3902"
// 	First operation:
// 	
// 		(s[0] + s[1]) % 10 = (3 + 9) % 10 = 2
// 		(s[1] + s[2]) % 10 = (9 + 0) % 10 = 9
// 		(s[2] + s[3]) % 10 = (0 + 2) % 10 = 2
// 		s becomes "292"
// 	
// 	
// 	Second operation:
// 	
// 		(s[0] + s[1]) % 10 = (2 + 9) % 10 = 1
// 		(s[1] + s[2]) % 10 = (9 + 2) % 10 = 1
// 		s becomes "11"
// 	
// 	
// 	Since the digits in "11" are the same, the output is true.
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of only digits.
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, dp-2d)
//   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
//   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
//   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
//   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
//   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
// - Binomial Coefficients (array, number, dp-1d, mod-exp)
//   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
//   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
//   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
//   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
//   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean hasSameDigits(String s) {
        int n = s.length();
        int[] count = new int[10];
        for (int i = 0; i < n; i++) {
            count[s.charAt(i) - '0']++;
        }
        for (int i = 0; i < 10; i++) {
            if (count[i] % 2 != 0) {
                return false;
            }
        }
        return true;            
    }
}
