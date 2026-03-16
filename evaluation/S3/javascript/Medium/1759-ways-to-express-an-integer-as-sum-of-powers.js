// Source: https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/   |   Difficulty: Medium
//
// Problem Description:
// Given two positive integers n and x.
//
// Return the number of ways n can be expressed as the sum of the xth power of unique positive integers, in other words, the number of sets of unique integers [n1, n2, ..., nk] where n = n1x + n2x + ... + nkx.
//
// Since the result can be very large, return it modulo 109 + 7.
//
// For example, if n = 160 and x = 3, one way to express n is n = 23 + 33 + 53.
//
// Example:
// Input: n = 10, x = 2
// Output: 1
// Explanation: We can express n as the following: n = 32 + 12 = 10.
// It can be shown that it is the only way to express 10 as the sum of the 2nd power of unique integers.
//
// Constraints:
// 1 <= n <= 300
// 	1 <= x <= 5
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, number, dp-1d, mod-exp)
//   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
//   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
//   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
//   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
//   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number} x
 * @return {number}
 */
var numberOfWays = function(n, x) {
    const MOD = 1e9 + 7;
    const maxBase = Math.floor(Math.pow(n, 1 / x));
    const dp = new Array(n + 1).fill(0);
    dp[0] = 1; // Base case: there's one way to sum to 0 (using no numbers)
    
    for (let base = 1; base <= maxBase; base++) {
        const power = Math.pow(base, x);
        for (let i = n; i >= power; i--) {
            dp[i] = (dp[i] + dp[i - power]) % MOD;
        }
    }
    return dp[n];
};
