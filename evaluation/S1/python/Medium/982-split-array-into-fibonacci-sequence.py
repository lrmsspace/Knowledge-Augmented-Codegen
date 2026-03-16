# Source: https://leetcode.com/problems/split-array-into-fibonacci-sequence/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string of digits num, such as "123456579". We can split it into a Fibonacci-like sequence [123, 456, 579].
#
# Formally, a Fibonacci-like sequence is a list f of non-negative integers such that:
#
#
# 	0 <= f[i] < 231, (that is, each integer fits in a 32-bit signed integer type),
# 	f.length >= 3, and
# 	f[i] + f[i + 1] == f[i + 2] for all 0 <= i < f.length - 2.
#
#
# Note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.
#
# Return any Fibonacci-like sequence split from num, or return [] if it cannot be done.
#
# Example:
# Input: num = "1101111"
# Output: [11,0,11,11]
# Explanation: The output [110, 1, 111] would also be accepted.
#
# Constraints:
# 1 <= num.length <= 200
# 	num contains only digits.
#
# Helpful references (internal KB):
# - palindrome-partitioning (string, array, backtracking, recursion)
#   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
#   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
#   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
#   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
#   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
# - Fibonacci Numbers (number, greedy, enumeration)
#   • When to use: When you need a unique, non-ambiguous binary representation of positive integers based on Fibonacci numbers, ensuring no two consecutive Fibonacci numbers are used in the sum.
#   • Idea: This algorithm encodes a positive integer into a unique binary string by greedily finding its Zeckendorf representation (sum of non-consecutive Fibonacci numbers). The encoding process typically involves iterating through Fibonacci numbers, resulting in a logarithmic time complexity relative to the input number's magnitude.
#   • Invariants: The remaining value 'n' to be encoded is always non-negative.; The partial binary code constructed so far represents a valid Zeckendorf sum of non-consecutive Fibonacci numbers.
#   • Tips: Precompute Fibonacci numbers up to a certain limit to optimize lookups.; Always start with the largest Fibonacci number less than or equal to the target value.
#   • Pitfalls: Incorrectly handling the base cases for small numbers like 1 or 2.; Forgetting to append the mandatory final '1' bit to the codeword.
# - Continued fractions (number, matrix-exp, segment-tree, recursion)
#   • When to use: When you need to represent real numbers as a sequence of integers, find optimal rational approximations, or solve certain number theoretic problems involving linear equations or quadratic irrationals.
#   • Idea: Continued fractions represent real numbers as an expression of the form a0 + 1/(a1 + 1/(a2 + ...)), providing a systematic way to find best rational approximations. They are fundamental in number theory, with convergent computation typically O(log N) for N terms.
#   • Invariants: The sequence of partial quotients (a_i) are positive integers for i >= 1.; Each convergent p_k/q_k is a best rational approximation of the original number.
#   • Tips: Understand the recursive definition and how to compute convergents.; The Euclidean algorithm is the basis for finite continued fractions.
#   • Pitfalls: Floating point precision issues when computing directly.; Incorrectly handling the base case or termination condition.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def splitIntoFibonacci(self, num):
        """
        :type num: str
        :rtype: List[int]
        """
        n = len(num)
        for i in range(1, min(10, n)):  # First number length
            if num[0] == '0' and i > 1:
                break
            a = int(num[:i])
            for j in range(i + 1, min(i + 10, n)):  # Second number length
                if num[i] == '0' and j - i > 1:
                    break
                b = int(num[i:j])
                fib = [a, b]
                k = j
                while k < n:
                    c = fib[-1] + fib[-2]
                    c_str = str(c)
                    c_len = len(c_str)
                    if k + c_len <= n and num[k:k + c_len] == c_str:
                        fib.append(c)
                        k += c_len
                    else:
                        break
                if k == n and len(fib) >= 3:
                    return fib
        return []