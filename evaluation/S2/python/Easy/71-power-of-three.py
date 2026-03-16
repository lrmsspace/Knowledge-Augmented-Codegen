# Source: https://leetcode.com/problems/power-of-three/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer n, return true if it is a power of three. Otherwise, return false.
#
# An integer n is a power of three, if there exists an integer x such that n == 3x.
#
# Example:
# Input: n = 27
# Output: true
# Explanation: 27 = 33
#
# Constraints:
# -231 <= n <= 231 - 1
#
#
#  
# Follow up: Could you solve it without loops/recursion?
#
# Helpful references (internal KB):
# - Binary Exponentiation (number, mod-exp, recursion)
#   • When to use: Use this algorithm to efficiently compute large integer powers of a number, especially when results need to be taken modulo a specific value. It is crucial for problems requiring powers with large exponents.
#   • Idea: Binary exponentiation, also known as exponentiation by squaring, computes a^n by breaking down the exponent n into its binary representation. This method significantly reduces the number of multiplications required, achieving an O(log n) time complexity.
#   • Invariants: In the iterative approach, (current_result * (original_base ^ original_exponent)) remains constant.; The exponent n is always non-negative and decreases towards zero.
#   • Tips: Apply the modulo operation at each multiplication step to prevent intermediate overflow.; The iterative approach is generally preferred over recursion to avoid potential stack overflow for very large exponents.
#   • Pitfalls: Forgetting to apply modulo at each step can lead to integer overflow, especially with large bases.; Incorrectly handling the base case for n=0 or n=1.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Ternary Search (interval, number, binary-search)
#   • When to use: Use when finding the extremum (maximum or minimum) of a unimodal function over a continuous interval, where the function strictly increases then decreases, or vice versa.
#   • Idea: Ternary search is an optimization algorithm that efficiently finds the extremum (maximum or minimum) of a unimodal function over a continuous interval. It operates in logarithmic time, O(log N), by repeatedly narrowing the search space.
#   • Invariants: The global extremum of the unimodal function is always contained within the current interval [l, r].; The function f(x) remains unimodal on the interval [l, r] throughout the search process.
#   • Tips: For floating-point functions, use a fixed number of iterations (e.g., 100-300) instead of an epsilon threshold for robustness.; The two comparison points m1 and m2 should divide the interval into three roughly equal parts for optimal convergence.
#   • Pitfalls: Applying ternary search to a non-unimodal function will not guarantee finding the global extremum.; Floating-point precision errors can lead to incorrect comparisons or infinite loops if epsilon is too small.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isPowerOfThree(self, n):
        """
        :type n: int
        :rtype: bool
        """
        if n <= 0:
            return False
        while n % 3 == 0:
            n //= 3
        return n == 1