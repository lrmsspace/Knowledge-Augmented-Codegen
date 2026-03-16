// Source: https://leetcode.com/problems/valid-permutations-for-di-sequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s of length n where s[i] is either:
//
//
// 	'D' means decreasing, or
// 	'I' means increasing.
//
//
// A permutation perm of n + 1 integers of all the integers in the range [0, n] is called a valid permutation if for all valid i:
//
//
// 	If s[i] == 'D', then perm[i] > perm[i + 1], and
// 	If s[i] == 'I', then perm[i] < perm[i + 1].
//
//
// Return the number of valid permutations perm. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: s = "DID"
// Output: 5
// Explanation: The 5 valid permutations of (0, 1, 2, 3) are:
// (1, 0, 3, 2)
// (2, 0, 3, 1)
// (2, 1, 3, 0)
// (3, 0, 2, 1)
// (3, 1, 2, 0)
//
// Constraints:
// n == s.length
// 	1 <= n <= 200
// 	s[i] is either 'I' or 'D'.
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, dp-2d)
//   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
//   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
//   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
//   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
//   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
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
 * @param {string} s
 * @return {number}
 */
var numPermsDISequence = function(s) {
    const mod = 1e9 + 7;
    const n = s.length;
    // Precompute factorials and inverse factorials for binomial coefficients
    const fact = new Array(n + 1).fill(1);
    const invFact = new Array(n + 1).fill(1);
    for (let i = 2; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[n] = modInverse(fact[n], mod);
    for (let i = n - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
        
    // Dynamic Programming approach
    const dp = Array(n + 1).fill(0);
    dp[0] = 1;
    for (let i = 0; i < n; i++) {
        const newDp = Array(n + 1).fill(0);
        if (s[i] === 'D') {
            let sum = 0;
            for (let j = n; j > 0; j--) {
                sum = (sum + dp[j]) % mod;
                newDp[j - 1] = sum;
            }
        } else {
            let sum = 0;
            for (let j = 0; j < n; j++) {
                sum = (sum + dp[j]) % mod;
                newDp[j + 1] = sum;
            }
        }
        for (let j = 0; j <= n; j++) {
            dp[j] = newDp[j];
        }
    }
    
    return dp[0];
    
    
};
