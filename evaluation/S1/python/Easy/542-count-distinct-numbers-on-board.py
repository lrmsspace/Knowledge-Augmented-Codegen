# Source: https://leetcode.com/problems/count-distinct-numbers-on-board/   |   Difficulty: Easy
#
# Problem Description:
# You are given a positive integer n, that is initially placed on a board. Every day, for 109 days, you perform the following procedure:
#
#
# 	For each number x present on the board, find all numbers 1 <= i <= n such that x % i == 1.
# 	Then, place those numbers on the board.
#
#
# Return the number of distinct integers present on the board after 109 days have elapsed.
#
# Note:
#
#
# 	Once a number is placed on the board, it will remain on it until the end.
# 	% stands for the modulo operation. For example, 14 % 3 is 2.
#
# Example:
# Input: n = 5
# Output: 4
# Explanation: Initially, 5 is present on the board. 
# The next day, 2 and 4 will be added since 5 % 2 == 1 and 5 % 4 == 1. 
# After that day, 3 will be added to the board because 4 % 3 == 1. 
# At the end of a billion days, the distinct numbers on the board will be 2, 3, 4, and 5.
#
# Constraints:
# 1 <= n <= 100
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def distinctIntegers(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1:
            return 1
        return n - 1