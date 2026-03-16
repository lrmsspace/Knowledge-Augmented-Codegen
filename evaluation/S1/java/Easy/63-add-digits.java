// Source: https://leetcode.com/problems/add-digits/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer num, repeatedly add all its digits until the result has only one digit, and return it.
//
// Example:
// Input: num = 38
// Output: 2
// Explanation: The process is
// 38 --> 3 + 8 --> 11
// 11 --> 1 + 1 --> 2 
// Since 2 has only one digit, return it.
//
// Constraints:
// 0 <= num <= 231 - 1
//
//
//  
// Follow up: Could you do it without any loop/recursion in O(1) runtime?
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Discrete Root
//  (number, mod-exp)
//   • When to use: Use this algorithm to find all solutions x for the modular equation x^k = a (mod n) when n is a prime number. It is applicable when solving for an unknown base in a modular power.
//   • Idea: This algorithm solves the discrete root problem by transforming it into a discrete logarithm problem using a primitive root modulo n. The overall time complexity is dominated by the discrete logarithm step, typically O(sqrt(n) log n) using Baby-step Giant-step.
//   • Invariants: All calculations are performed within the finite field modulo n.; The primitive root g generates all non-zero residues modulo n.
//   • Tips: Handle the special case where a = 0 separately, as x = 0 is the only solution.; Ensure the modulus n is prime, as primitive roots are guaranteed to exist.
//   • Pitfalls: Assuming n is prime when it is not, which invalidates the primitive root approach.; Forgetting to check for the existence of solutions for the discrete logarithm.
// - Bit manipulation (number, counting, recursion)
//   • When to use: Use for efficient low-level operations on integers, checking properties related to powers of two, or manipulating individual bits. It provides constant-time solutions for many numerical checks.
//   • Idea: This card covers fundamental bitwise operations for checking number properties like divisibility by powers of two, identifying powers of two, and manipulating individual bits. These operations typically run in O(1) time complexity.
//   • Invariants: For a positive integer `n`, `(n & (n - 1)) == 0` if and only if `n` is a power of two.; An integer `n` is divisible by `2^k` if and only if its `k` least significant bits are all zero, which is checked by `(n & ((1 << k) - 1)) == 0`.
//   • Tips: Use `n & 1` to efficiently check if a number `n` is odd or even.; The expression `1 << k` calculates 2 raised to the power of `k`.
//   • Pitfalls: When checking if a number is a power of two, remember to handle the `n == 0` case separately as `0 & (-1)` is `0`.; Be cautious with integer overflow when performing left shifts (`1 << k`) for large `k` values.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int addDigits(int num) {
        if (num == 0) {
            return 0;
        }
        return 1 + (num - 1) % 9;           
    }
}
