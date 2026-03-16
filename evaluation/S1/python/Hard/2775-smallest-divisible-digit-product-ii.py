# Source: https://leetcode.com/problems/smallest-divisible-digit-product-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string num which represents a positive integer, and an integer t.
#
# A number is called zero-free if none of its digits are 0.
#
# Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".
#
# Example:
# Input: num = "1234", t = 256
#
# Output: "1488"
#
# Explanation:
#
# The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.
#
# Constraints:
# 2 <= num.length <= 2 * 105
# 	num consists only of digits in the range ['0', '9'].
# 	num does not contain leading zeros.
# 	1 <= t <= 1014
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Primality tests (number, enumeration, simulation)
#   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
#   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
#   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
#   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
#   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
# - Suffix Automaton (graph, string, simulation)
#   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
#   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
#   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
#   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
#   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def smallestNumber(self, num, t):
        """
        :type num: str
        :type t: int
        :rtype: str
        """
        from math import gcd
        from functools import reduce

        # Step 1: Factor t into its prime factors
        def prime_factors(x):
            factors = {}
            d = 2
            while d * d <= x:
                while (x % d) == 0:
                    factors[d] = factors.get(d, 0) + 1
                    x //= d
                d += 1
            if x > 1:
                factors[x] = factors.get(x, 0) + 1
            return factors

        t_factors = prime_factors(t)

        # Step 2: Check if it's possible to form such a number
        if any(p > 7 for p in t_factors):
            return "-1"

        # Step 3: Construct the smallest number >= num with product divisible by t
        def construct_number(num, t_factors):
            from itertools import product

            digits = [str(i) for i in range(1, 10)]
            length = len(num)

            for l in range(length, length + 2):  # Check lengths length and length + 1
                for comb in product(digits, repeat=l):
                    candidate = ''.join(comb)
                    if candidate >= num:
                        prod_factors = {}
                        for d in candidate:
                            d_int = int(d)
                            for p, cnt in prime_factors(d_int).items():
                                prod_factors[p] = prod_factors.get(p, 0) + cnt

                        if all(prod_factors.get(p, 0) >= cnt for p, cnt in t_factors.items()):
                            return candidate
            return "-1"

        return construct_number(num, t_factors) 
            