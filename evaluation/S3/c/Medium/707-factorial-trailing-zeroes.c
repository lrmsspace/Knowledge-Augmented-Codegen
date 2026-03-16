// Source: https://leetcode.com/problems/factorial-trailing-zeroes/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the number of trailing zeroes in n!.
//
// Note that n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1.
//
// Example:
// Input: n = 3
// Output: 0
// Explanation: 3! = 6, no trailing zero.
//
// Constraints:
// 0 <= n <= 104
//
//
//  
// Follow up: Could you write a solution that works in logarithmic time complexity?
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int trailingZeroes(int n) {
    int count = 0;
    while (n > 0) {
        n /= 5;
        count += n;
    }
    return count;       
}
