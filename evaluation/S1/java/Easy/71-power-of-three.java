// Source: https://leetcode.com/problems/power-of-three/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if it is a power of three. Otherwise, return false.
//
// An integer n is a power of three, if there exists an integer x such that n == 3x.
//
// Example:
// Input: n = 27
// Output: true
// Explanation: 27 = 33
//
// Constraints:
// -231 <= n <= 231 - 1
//
//
//  
// Follow up: Could you solve it without loops/recursion?
//
// Helpful references (internal KB):
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Binary Exponentiation (number, mod-exp, recursion)
//   • When to use: Use this algorithm to efficiently compute large integer powers of a number, especially when results need to be taken modulo a specific value. It is crucial for problems requiring powers with large exponents.
//   • Idea: Binary exponentiation, also known as exponentiation by squaring, computes a^n by breaking down the exponent n into its binary representation. This method significantly reduces the number of multiplications required, achieving an O(log n) time complexity.
//   • Invariants: In the iterative approach, (current_result * (original_base ^ original_exponent)) remains constant.; The exponent n is always non-negative and decreases towards zero.
//   • Tips: Apply the modulo operation at each multiplication step to prevent intermediate overflow.; The iterative approach is generally preferred over recursion to avoid potential stack overflow for very large exponents.
//   • Pitfalls: Forgetting to apply modulo at each step can lead to integer overflow, especially with large bases.; Incorrectly handling the base case for n=0 or n=1.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean isPowerOfThree(int n) {
        if (n <= 0) {
            return false;
        }
        // The largest power of 3 that fits in a 32-bit signed integer is 3^19 = 1162261467
        return 1162261467 % n == 0;         
    }
}
