// Source: https://leetcode.com/problems/count-the-number-of-ideal-arrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers n and maxValue, which are used to describe an ideal array.
//
// A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:
//
//
// 	Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
// 	Every arr[i] is divisible by arr[i - 1], for 0 < i < n.
//
//
// Return the number of distinct ideal arrays of length n. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 2, maxValue = 5
// Output: 10
// Explanation: The following are the possible ideal arrays:
// - Arrays starting with the value 1 (5 arrays): [1,1], [1,2], [1,3], [1,4], [1,5]
// - Arrays starting with the value 2 (2 arrays): [2,2], [2,4]
// - Arrays starting with the value 3 (1 array): [3,3]
// - Arrays starting with the value 4 (1 array): [4,4]
// - Arrays starting with the value 5 (1 array): [5,5]
// There are a total of 5 + 2 + 1 + 1 + 1 = 10 distinct ideal arrays.
//
// Constraints:
// 2 <= n <= 104
// 	1 <= maxValue <= 104
//
// Helpful references (internal KB):
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
// - Primitive Root (number, mod-exp, sieve, enumeration)
//   • When to use: Use when needing to find a generator for the multiplicative group of integers modulo n, or to check if a number is a primitive root. This is often required in number theory problems involving modular arithmetic and cyclic groups.
//   • Idea: This algorithm finds a primitive root modulo n by checking candidate numbers and verifying their order using Euler's totient function and its prime factors. The optimized approach significantly reduces checks from O(phi(n)) to O(k * log(n)) for each candidate, where k is the number of distinct prime factors of phi(n).
//   • Invariants: The current candidate g is coprime to n.; The order of g modulo n is being checked against divisors of phi(n).
//   • Tips: First, determine if a primitive root exists for the given n.; Calculate Euler's totient function phi(n) for the modulus n.
//   • Pitfalls: Forgetting to check the existence condition for primitive roots.; Incorrectly calculating Euler's totient function phi(n).
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int idealArrays(int n, int maxValue) {
    // This problem can be solved using dynamic programming and combinatorial mathematics.
    // The idea is to count the number of ways to create an ideal array of length n with values up to maxValue.
    // We can use a 2D DP array where dp[i][j] represents the number of ideal arrays of length i that end with the value j.
    // The transition will be based on the divisibility condition, where dp[i][j] can be derived from dp[i-1][k] for all k that divides j.

    int mod = 1000000007;
    int dp[n + 1][maxValue + 1];
    
    // Initialize the dp array
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= maxValue; j++) {
            dp[i][j] = 0;
        }
    }

    // Base case: There is one ideal array of length 1 for each value from 1 to maxValue
    for (int j = 1; j <= maxValue; j++) {
        dp[1][j] = 1;
    }

    // Fill the dp array
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= maxValue; j++) {
            for (int k = 1; k < j; k++) {
                if (j % k == 0) { // If k divides j
                    dp[i][j] = (dp[i][j] + dp[i - 1][k]) % mod;
                }
            }
        }
    }

    // Sum up all the ideal arrays of length n
    int result = 0;
    for (int j = 1; j <= maxValue; j++) {
        result = (result + dp[n][j]) % mod;
    }

    return result;      
}
