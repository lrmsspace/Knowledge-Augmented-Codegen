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
// - Factorial modulo 
// p (number, array, recursion, mod-exp, dp-1d)
//   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
//   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
//   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
//   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
//   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
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
    dp[0] = 1; // Base case: one way to sum to zero (using no numbers)
    
    for (let base = 1; base <= maxBase; base++) {
        const power = Math.pow(base, x);
        for (let i = n; i >= power; i--) {
            dp[i] = (dp[i] + dp[i - power]) % MOD;
        }
    }
    
    return dp[n];
};
