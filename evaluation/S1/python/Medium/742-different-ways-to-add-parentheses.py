# Source: https://leetcode.com/problems/different-ways-to-add-parentheses/   |   Difficulty: Medium
#
# Problem Description:
# Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.
#
# The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.
#
# Example:
# Input: expression = "2-1-1"
# Output: [0,2]
# Explanation:
# ((2-1)-1) = 0 
# (2-(1-1)) = 2
#
# Constraints:
# 1 <= expression.length <= 20
# 	expression consists of digits and the operator '+', '-', and '*'.
# 	All the integer values in the input expression are in the range [0, 99].
# 	The integer values in the input expression do not have a leading '-' or '+' denoting the sign.
#
# Helpful references (internal KB):
# - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
#   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
#   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
#   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
#   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
#   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
# - palindrome-partitioning (string, array, backtracking, recursion)
#   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
#   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
#   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
#   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
#   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
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
    def diffWaysToCompute(self, expression):
        """
        :type expression: str
        :rtype: List[int]
        """
        memo = {}

        def ways(expr):
            if expr in memo:
                return memo[expr]

            res = []
            for i, char in enumerate(expr):
                if char in "+-*":
                    left = ways(expr[:i])
                    right = ways(expr[i+1:])

                    for l in left:
                        for r in right:
                            if char == '+':
                                res.append(l + r)
                            elif char == '-':
                                res.append(l - r)
                            elif char == '*':
                                res.append(l * r)

            if not res:
                res.append(int(expr))

            memo[expr] = res
            return res

        return ways(expression)