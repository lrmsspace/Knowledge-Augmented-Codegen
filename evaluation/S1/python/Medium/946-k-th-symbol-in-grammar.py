# Source: https://leetcode.com/problems/k-th-symbol-in-grammar/   |   Difficulty: Medium
#
# Problem Description:
# We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.
#
#
# 	For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.
#
#
# Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.
#
# Example:
# Input: n = 1, k = 1
# Output: 0
# Explanation: row 1: 0
#
# Constraints:
# 1 <= n <= 30
# 	1 <= k <= 2n - 1
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
    def kthGrammar(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        if n == 1:
            return 0
        mid = 2 ** (n - 1) // 2
        if k <= mid:
            return self.kthGrammar(n - 1, k)
        else:
            return 1 - self.kthGrammar(n - 1, k - mid)