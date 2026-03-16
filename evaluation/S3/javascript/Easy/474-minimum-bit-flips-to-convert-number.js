// Source: https://leetcode.com/problems/minimum-bit-flips-to-convert-number/   |   Difficulty: Easy
//
// Problem Description:
// A bit flip of a number x is choosing a bit in the binary representation of x and flipping it from either 0 to 1 or 1 to 0.
//
//
// 	For example, for x = 7, the binary representation is 111 and we may choose any bit (including any leading zeros not shown) and flip it. We can flip the first bit from the right to get 110, flip the second bit from the right to get 101, flip the fifth bit from the right (a leading zero) to get 10111, etc.
//
//
// Given two integers start and goal, return the minimum number of bit flips to convert start to goal.
//
// Example:
// Input: start = 10, goal = 7
// Output: 3
// Explanation: The binary representation of 10 and 7 are 1010 and 0111 respectively. We can convert 10 to 7 in 3 steps:
// - Flip the first bit from the right: 1010 -> 1011.
// - Flip the third bit from the right: 1011 -> 1111.
// - Flip the fourth bit from the right: 1111 -> 0111.
// It can be shown we cannot convert 10 to 7 in less than 3 steps. Hence, we return 3.
//
// Constraints:
// 0 <= start, goal <= 109
//
//
//  
// Note: This question is the same as 461: Hamming Distance.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Bit manipulation (number, counting)
//   • When to use: When you need to manipulate individual bits within an integer, optimize space, or perform fast operations on boolean flags or small sets. It's ideal for low-level control and specific integer property checks.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators like AND, OR, XOR, NOT, and shifts. These operations allow for efficient setting, clearing, flipping, and checking of individual bits, typically with O(1) complexity per operation.
//   • Invariants: The state of any bit `i` where `i != x` is preserved during an operation on the `x`-th bit.; After `n = n | (1 << x)`, the `x`-th bit of `n` is 1.
//   • Tips: Use `1 << x` to create a mask for the x-th bit.; Understand the difference between `&`, `|`, `^`, `~`, `<<`, `>>` operators.
//   • Pitfalls: Incorrect operator precedence (e.g., `&` vs `&&`).; Off-by-one errors with bit indices (0-indexed vs 1-indexed).
// - Bit manipulation (number, counting, recursion)
//   • When to use: Use for efficient low-level operations on integers, checking properties related to powers of two, or manipulating individual bits. It provides constant-time solutions for many numerical checks.
//   • Idea: This card covers fundamental bitwise operations for checking number properties like divisibility by powers of two, identifying powers of two, and manipulating individual bits. These operations typically run in O(1) time complexity.
//   • Invariants: For a positive integer `n`, `(n & (n - 1)) == 0` if and only if `n` is a power of two.; An integer `n` is divisible by `2^k` if and only if its `k` least significant bits are all zero, which is checked by `(n & ((1 << k) - 1)) == 0`.
//   • Tips: Use `n & 1` to efficiently check if a number `n` is odd or even.; The expression `1 << k` calculates 2 raised to the power of `k`.
//   • Pitfalls: When checking if a number is a power of two, remember to handle the `n == 0` case separately as `0 & (-1)` is `0`.; Be cautious with integer overflow when performing left shifts (`1 << k`) for large `k` values.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} start
 * @param {number} goal
 * @return {number}
 */
var minBitFlips = function(start, goal) {
    // The number of bit flips required is equal to the number of bits that are different between start and goal
    // We can find this by taking the XOR of start and goal, which will give us a number where each bit is 1 if the bits of start and goal are different at that position
    // Then we can count the number of 1s in the result to get the number of bit flips needed
    let xor = start ^ goal; // XOR to find differing bits
    let flips = 0; // Initialize flip count
    while (xor > 0) {
        flips += xor & 1; // Increment flips if the least significant bit is 1
        xor >>= 1; // Right shift to check the next bit
    }
    return flips; // Return the total number of flips needed
};
