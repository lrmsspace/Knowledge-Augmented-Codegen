// Source: https://leetcode.com/problems/power-of-two/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if it is a power of two. Otherwise, return false.
//
// An integer n is a power of two, if there exists an integer x such that n == 2x.
//
// Example:
// Input: n = 1
// Output: true
// Explanation: 20 = 1
//
// Constraints:
// -231 <= n <= 231 - 1
//
//
//  
// Follow up: Could you solve it without loops/recursion?
//
// Helpful references (internal KB):
// - Bit manipulation (number, counting, recursion)
//   • When to use: Use for efficient low-level operations on integers, checking properties related to powers of two, or manipulating individual bits. It provides constant-time solutions for many numerical checks.
//   • Idea: This card covers fundamental bitwise operations for checking number properties like divisibility by powers of two, identifying powers of two, and manipulating individual bits. These operations typically run in O(1) time complexity.
//   • Invariants: For a positive integer `n`, `(n & (n - 1)) == 0` if and only if `n` is a power of two.; An integer `n` is divisible by `2^k` if and only if its `k` least significant bits are all zero, which is checked by `(n & ((1 << k) - 1)) == 0`.
//   • Tips: Use `n & 1` to efficiently check if a number `n` is odd or even.; The expression `1 << k` calculates 2 raised to the power of `k`.
//   • Pitfalls: When checking if a number is a power of two, remember to handle the `n == 0` case separately as `0 & (-1)` is `0`.; Be cautious with integer overflow when performing left shifts (`1 << k`) for large `k` values.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Binary Exponentiation (number, mod-exp, divide-and-conquer)
//   • When to use: Use when calculating a^n efficiently, especially for large n or when results need to be taken modulo some number. It reduces the number of multiplications from linear to logarithmic.
//   • Idea: Binary exponentiation computes a^n by repeatedly squaring the base and multiplying terms corresponding to the set bits in the exponent's binary representation. This method achieves a time complexity of O(log n) multiplications.
//   • Invariants: The product of `result` and `current_base` raised to the `remaining_exponent` equals the initial `a^N`.; `current_base` always represents `a` raised to the power of `2^k` for the current iteration `k`.
//   • Tips: Handle base cases like n=0 (result is 1) and n=1 (result is a).; Use long long or appropriate large integer types for intermediate products to prevent overflow.
//   • Pitfalls: Integer overflow if not using appropriate data types or modulo arithmetic.; Incorrectly handling negative exponents (typically not covered by basic binary exponentiation).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @return {boolean}
 */
var isPowerOfTwo = function(n) {
    return n > 0 && (n & (n - 1)) === 0;
};
