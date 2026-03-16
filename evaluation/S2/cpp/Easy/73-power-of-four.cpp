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
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Binary Exponentiation by Factoring (number, mod-exp)
//   • When to use: Use when computing modular exponentiation $ax^y \pmod{2^d}$ where the modulus is a power of two ($2^d$ with $d \geq 3$) and the base $x$ is odd. It leverages the specific structure of the multiplicative group modulo $2^d$ for efficient calculation.
//   • Idea: This algorithm computes $ax^y \pmod{2^d}$ for odd $x$ by transforming the problem using a 'logarithm' $L(x)$ and a fixed base $b \equiv 5 \pmod 8$. It achieves $O(d)$ complexity for the exponentiation and logarithm parts, plus a single multiplication by $y$.
//   • Invariants: The intermediate result is always congruent to the original expression modulo $2^d$.; The base used for exponentiation is always odd and congruent to $1 \pmod 4$ (after potential transformation).
//   • Tips: Handle $x \equiv 3 \pmod 4$ by transforming $x \mapsto -x$ and $a \mapsto (-1)^y a$.; The modulus $2^d$ must have $d \geq 3$ for the group structure to apply.
//   • Pitfalls: Incorrectly handling the $x \equiv 3 \pmod 4$ case or its sign implications.; Applying the method to even bases $x$, which breaks the underlying group structure.
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
        // Check if n is positive, a power of two, and has its single '1' bit at an even position.
        return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555) != 0;            
    }
};
