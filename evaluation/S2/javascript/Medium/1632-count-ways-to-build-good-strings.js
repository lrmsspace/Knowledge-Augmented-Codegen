// Source: https://leetcode.com/problems/count-ways-to-build-good-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given the integers zero, one, low, and high, we can construct a string by starting with an empty string, and then at each step perform either of the following:
//
//
// 	Append the character '0' zero times.
// 	Append the character '1' one times.
//
//
// This can be performed any number of times.
//
// A good string is a string constructed by the above process having a length between low and high (inclusive).
//
// Return the number of different good strings that can be constructed satisfying these properties. Since the answer can be large, return it modulo 109 + 7.
//
// Example:
// Input: low = 3, high = 3, zero = 1, one = 1
// Output: 8
// Explanation: 
// One possible valid good string is "011". 
// It can be constructed as follows: "" -> "0" -> "01" -> "011". 
// All binary strings from "000" to "111" are good strings in this example.
//
// Constraints:
// 1 <= low <= high <= 105
// 	1 <= zero, one <= low
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Binomial Coefficients (number, recursion)
//   • When to use: Use when computing C(n, k) modulo m where n is large and m is small, especially when m is prime, a prime power, or a composite number with small prime factors.
//   • Idea: This technique computes binomial coefficients C(n, k) modulo m, particularly when n is very large and m is small. It leverages modular arithmetic properties, such as Lucas's Theorem for prime moduli or the Chinese Remainder Theorem for composite moduli, achieving complexities like O(m + log_m n).
//   • Invariants: For C(N, K) mod M, the recursive calls C(N/M, K/M) and C(N%M, K%M) are valid subproblems.; All factorial and inverse factorial values used for C(x, y) where x, y < M are precomputed modulo M.
//   • Tips: Precompute factorials and inverse factorials modulo m for efficient base case calculations.; Apply Lucas's Theorem when the modulus m is prime to break down the problem recursively.
//   • Pitfalls: Failing to handle k > n correctly, which should yield 0.; Incorrectly applying Lucas's Theorem when the modulus is not prime.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} low
 * @param {number} high
 * @param {number} zero
 * @param {number} one
 * @return {number}
 */
var countGoodStrings = function(low, high, zero, one) {
    const mod = 1e9 + 7;
    const dp = new Array(high + 1).fill(0);
    dp[0] = 1;
    for (let length = 1; length <= high; length++) {
        if (length >= zero) {
            dp[length] = (dp[length] + dp[length - zero]) % mod;
        }
        if (length >= one) {
            dp[length] = (dp[length] + dp[length - one]) % mod;
        }
    }
    let count = 0;
    for (let length = low; length <= high; length++) {
        count = (count + dp[length]) % mod;
    }
    return count;
};
