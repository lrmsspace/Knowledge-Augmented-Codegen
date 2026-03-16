// Source: https://leetcode.com/problems/number-of-1-bits/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).
//
// Example:
// Input: n = 11
//
// Output: 3
//
// Explanation:
//
// The input binary string 1011 has a total of three set bits.
//
// Constraints:
// 1 <= n <= 231 - 1
//
//
//  
// Follow up: If this function is called many times, how would you optimize it?
//
// Helpful references (internal KB):
// - Bit manipulation (number, counting, recursion)
//   • When to use: Use for efficient low-level operations on integers, checking properties related to powers of two, or manipulating individual bits. It provides constant-time solutions for many numerical checks.
//   • Idea: This card covers fundamental bitwise operations for checking number properties like divisibility by powers of two, identifying powers of two, and manipulating individual bits. These operations typically run in O(1) time complexity.
//   • Invariants: For a positive integer `n`, `(n & (n - 1)) == 0` if and only if `n` is a power of two.; An integer `n` is divisible by `2^k` if and only if its `k` least significant bits are all zero, which is checked by `(n & ((1 << k) - 1)) == 0`.
//   • Tips: Use `n & 1` to efficiently check if a number `n` is odd or even.; The expression `1 << k` calculates 2 raised to the power of `k`.
//   • Pitfalls: When checking if a number is a power of two, remember to handle the `n == 0` case separately as `0 & (-1)` is `0`.; Be cautious with integer overflow when performing left shifts (`1 << k`) for large `k` values.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Gray code (number, prefix-xor)
//   • When to use: Use when a sequence of binary numbers is needed where successive values differ by only one bit. This is useful for error detection in digital systems or position encoders.
//   • Idea: Gray code is a binary numeral system where two successive values differ in only one bit position. Conversion from a binary number `n` to its Gray code `G(n)` is `n ^ (n >> 1)`, and the inverse operation can also be performed efficiently in O(log N) time.
//   • Invariants: For binary to Gray: The resulting Gray code `G(n)` differs from `n` by exactly one bit for each `n`.; For inverse Gray to binary: The variable `n` accumulates the correct binary value from MSB to LSB.
//   • Tips: Understand the core `n ^ (n >> 1)` transformation for binary to Gray.; The inverse Gray code conversion involves iteratively XORing with right-shifted values.
//   • Pitfalls: Confusing Gray code with standard binary representation.; Incorrectly implementing the iterative inverse transformation logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @return {number}
 */
var hammingWeight = function(n) {
    let count = 0;
    
    while (n !== 0) {
        count += n & 1;
        n = n >>> 1; // Use unsigned right shift to handle negative numbers correctly
    }
    
    return count;
};
