# Source: https://leetcode.com/problems/super-pow/   |   Difficulty: Medium
#
# Problem Description:
# Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.
#
# Example:
# Input: a = 2, b = [3]
# Output: 8
#
# Constraints:
# 1 <= a <= 231 - 1
# 	1 <= b.length <= 2000
# 	0 <= b[i] <= 9
# 	b does not contain leading zeros.
#
# Helpful references (internal KB):
# - Binary Exponentiation (number, mod-exp, divide-and-conquer)
#   • When to use: Use when calculating a^n efficiently, especially for large n or when results need to be taken modulo some number. It reduces the number of multiplications from linear to logarithmic.
#   • Idea: Binary exponentiation computes a^n by repeatedly squaring the base and multiplying terms corresponding to the set bits in the exponent's binary representation. This method achieves a time complexity of O(log n) multiplications.
#   • Invariants: The product of `result` and `current_base` raised to the `remaining_exponent` equals the initial `a^N`.; `current_base` always represents `a` raised to the power of `2^k` for the current iteration `k`.
#   • Tips: Handle base cases like n=0 (result is 1) and n=1 (result is a).; Use long long or appropriate large integer types for intermediate products to prevent overflow.
#   • Pitfalls: Integer overflow if not using appropriate data types or modulo arithmetic.; Incorrectly handling negative exponents (typically not covered by basic binary exponentiation).
# - Binary Exponentiation (number, mod-exp, recursion)
#   • When to use: Use this algorithm to efficiently compute large integer powers of a number, especially when results need to be taken modulo a specific value. It is crucial for problems requiring powers with large exponents.
#   • Idea: Binary exponentiation, also known as exponentiation by squaring, computes a^n by breaking down the exponent n into its binary representation. This method significantly reduces the number of multiplications required, achieving an O(log n) time complexity.
#   • Invariants: In the iterative approach, (current_result * (original_base ^ original_exponent)) remains constant.; The exponent n is always non-negative and decreases towards zero.
#   • Tips: Apply the modulo operation at each multiplication step to prevent intermediate overflow.; The iterative approach is generally preferred over recursion to avoid potential stack overflow for very large exponents.
#   • Pitfalls: Forgetting to apply modulo at each step can lead to integer overflow, especially with large bases.; Incorrectly handling the base case for n=0 or n=1.
# - Factorial modulo 
# p (number, array, recursion, mod-exp, dp-1d)
#   • When to use: Use when computing powers of numbers modulo another number, especially with very large exponents, to prevent overflow and ensure correctness.
#   • Idea: Modular exponentiation computes the remainder of a large positive integer power divided by another positive integer. It runs in O(log exponent) time complexity.
#   • Invariants: The current result `res` accumulates the product of `base` terms modulo `modulus`.; The `exponent` variable always represents the remaining power to be applied.
#   • Tips: Use binary exponentiation (exponentiation by squaring) for efficiency.; Handle base, exponent, and modulus carefully for edge cases like zero or one.
#   • Pitfalls: Forgetting to apply modulo at each step, leading to overflow.; Incorrectly handling negative exponents (if applicable, though usually positive).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def superPow(self, a, b):
        """
        :type a: int
        :type b: List[int]
        :rtype: int
        """
        MOD = 1337
        
        def mod_exp(x, n):
            result = 1
            x = x % MOD
            
            while n > 0:
                if n % 2 == 1:  # If n is odd
                    result = (result * x) % MOD
                x = (x * x) % MOD
                n //= 2
            
            return result
        
        def super_pow_helper(a, b):
            if not b:
                return 1
            last_digit = b.pop()
            part1 = mod_exp(a, last_digit)
            part2 = mod_exp(super_pow_helper(a, b), 10)
            return (part1 * part2) % MOD
        
        return super_pow_helper(a, b)