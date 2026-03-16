# Source: https://leetcode.com/problems/airplane-seat-assignment-probability/   |   Difficulty: Medium
#
# Problem Description:
# n passengers board an airplane with exactly n seats. The first passenger has lost the ticket and picks a seat randomly. But after that, the rest of the passengers will:
#
#
# 	Take their own seat if it is still available, and
# 	Pick other seats randomly when they find their seat occupied
#
#
# Return the probability that the nth person gets his own seat.
#
# Example:
# Input: n = 1
# Output: 1.00000
# Explanation: The first person can only get the first seat.
#
# Constraints:
# 1 <= n <= 105
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
    def nthPersonGetsNthSeat(self, n):
        """
        :type n: int
        :rtype: float
        """
        if n == 1:
            return 1.0
        else:
            return 0.5