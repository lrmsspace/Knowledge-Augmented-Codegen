# Source: https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/   |   Difficulty: Hard
#
# Problem Description:
# There are n oranges in the kitchen and you decided to eat some of these oranges every day as follows:
#
#
# 	Eat one orange.
# 	If the number of remaining oranges n is divisible by 2 then you can eat n / 2 oranges.
# 	If the number of remaining oranges n is divisible by 3 then you can eat 2 * (n / 3) oranges.
#
#
# You can only choose one of the actions per day.
#
# Given the integer n, return the minimum number of days to eat n oranges.
#
# Example:
# Input: n = 10
# Output: 4
# Explanation: You have 10 oranges.
# Day 1: Eat 1 orange,  10 - 1 = 9.  
# Day 2: Eat 6 oranges, 9 - 2*(9/3) = 9 - 6 = 3. (Since 9 is divisible by 3)
# Day 3: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1. 
# Day 4: Eat the last orange  1 - 1  = 0.
# You need at least 4 days to eat the 10 oranges.
#
# Constraints:
# 1 <= n <= 2 * 109
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Integer factorization (number, enumeration)
#   • When to use: Use when needing to decompose a composite integer into its prime factors, especially for numbers where trial division is feasible. It's suitable for problems requiring the unique prime components of a number.
#   • Idea: Integer factorization decomposes a given composite number into a product of its prime factors. The most common approach, trial division, involves testing divisibility by prime numbers up to the square root of the number, with optimizations for small primes and patterns like modulo 6.
#   • Invariants: The product of found prime factors multiplied by the current number equals the original number.; All prime factors found so far are less than or equal to the current trial divisor.
#   • Tips: Handle small prime factors (2, 3, 5) separately for efficiency.; Optimize trial division by checking only primes or numbers of form 6k +/- 1.
#   • Pitfalls: Forgetting to handle the case where the remaining number is a prime factor itself.; Inefficiently checking all numbers instead of only potential prime divisors.
# - Linear Diophantine Equation (number, greedy)
#   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
#   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
#   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
#   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
#   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minDays(self, n):
        """
        :type n: int
        :rtype: int
        """
        from functools import lru_cache

        @lru_cache(maxsize=None)
        def dfs(x):
            if x <= 1:
                return x
            res = 1 + dfs(x - 1)  # Eat one orange
            if x % 2 == 0:
                res = min(res, 1 + dfs(x // 2))  # Eat n/2 oranges
            if x % 3 == 0:
                res = min(res, 1 + dfs(x - 2 * (x // 3)))  # Eat 2*(n/3) oranges
            return res

        return dfs(n)