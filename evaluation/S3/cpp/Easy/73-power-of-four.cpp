// Source: https://leetcode.com/problems/power-of-four/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if it is a power of four. Otherwise, return false.
//
// An integer n is a power of four, if there exists an integer x such that n == 4x.
//
// Example:
// Input: n = 16
// Output: true
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
// - Bit manipulation (number, enumeration, simulation)
//   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
//   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
//   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
//   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
// - Bit manipulation (number, counting)
//   • When to use: When you need to manipulate individual bits within an integer, optimize space, or perform fast operations on boolean flags or small sets. It's ideal for low-level control and specific integer property checks.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators like AND, OR, XOR, NOT, and shifts. These operations allow for efficient setting, clearing, flipping, and checking of individual bits, typically with O(1) complexity per operation.
//   • Invariants: The state of any bit `i` where `i != x` is preserved during an operation on the `x`-th bit.; After `n = n | (1 << x)`, the `x`-th bit of `n` is 1.
//   • Tips: Use `1 << x` to create a mask for the x-th bit.; Understand the difference between `&`, `|`, `^`, `~`, `<<`, `>>` operators.
//   • Pitfalls: Incorrect operator precedence (e.g., `&` vs `&&`).; Off-by-one errors with bit indices (0-indexed vs 1-indexed).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool isPowerOfFour(int n) {
        if (n <= 0) return false; // Powers of four are positive integers
        if ((n & (n - 1)) != 0) return false; // Check if n is a power of two
        if ((n & 0x55555555) == 0) return false; // Check if the single set bit is in the correct position for powers of four
        return true;            
    }
};
