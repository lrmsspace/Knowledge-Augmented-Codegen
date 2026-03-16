// Source: https://leetcode.com/problems/nth-digit/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the nth digit of the infinite integer sequence [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].
//
// Example:
// Input: n = 3
// Output: 3
//
// Constraints:
// 1 <= n <= 231 - 1
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Primality tests (number, mod-exp, randomized, probability-statistics, simulation)
//   • When to use: Use when needing to efficiently determine if a large number is prime or composite, especially for cryptographic applications or number theory problems. It's suitable for verifying primality with high probability, or deterministically for numbers within certain bounds.
//   • Idea: The Miller-Rabin primality test is a probabilistic algorithm that determines if a given number is composite or a strong probable prime. It leverages properties of modular arithmetic and Fermat's Little Theorem to achieve a polynomial time complexity, typically O(k * log^3 n) for k iterations.
//   • Invariants: The number `n` being tested is an odd integer greater than 2.; The expression `n-1` is decomposed into `2^s * d`, where `d` is an odd integer.
//   • Tips: Pre-check for small prime divisors to quickly filter out many composite numbers.; Perform multiple iterations with different random bases to increase the certainty of primality.
//   • Pitfalls: The probabilistic version can yield false positives (strong probable primes) if too few bases are tested.; Incorrectly implementing modular exponentiation can lead to incorrect results or performance issues.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findNthDigit(int n) {
    long long digit_length = 1; // Current digit length
    long long count = 9;        // Count of numbers with current digit length
    long long start = 1;       // Starting number with current digit length

    // Find the range where the nth digit is located
    while (n > digit_length * count) {
        n -= digit_length * count;
        digit_length++;
        count *= 10;
        start *= 10;
    }

    // Find the actual number that contains the nth digit
    start += (n - 1) / digit_length;
    char num_str[20];
    sprintf(num_str, "%lld", start);

    // Find the specific digit in that number
    return num_str[(n - 1) % digit_length] - '0';       
}
