# Source: https://leetcode.com/problems/first-day-where-you-have-been-in-all-the-rooms/   |   Difficulty: Medium
#
# Problem Description:
# There are n rooms you need to visit, labeled from 0 to n - 1. Each day is labeled, starting from 0. You will go in and visit one room a day.
#
# Initially on day 0, you visit room 0. The order you visit the rooms for the coming days is determined by the following rules and a given 0-indexed array nextVisit of length n:
#
#
# 	Assuming that on a day, you visit room i,
# 	if you have been in room i an odd number of times (including the current visit), on the next day you will visit a room with a lower or equal room number specified by nextVisit[i] where 0 <= nextVisit[i] <= i;
# 	if you have been in room i an even number of times (including the current visit), on the next day you will visit room (i + 1) mod n.
#
#
# Return the label of the first day where you have been in all the rooms. It can be shown that such a day exists. Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nextVisit = [0,0]
# Output: 2
# Explanation:
# - On day 0, you visit room 0. The total times you have been in room 0 is 1, which is odd.
#   On the next day you will visit room nextVisit[0] = 0
# - On day 1, you visit room 0, The total times you have been in room 0 is 2, which is even.
#   On the next day you will visit room (0 + 1) mod 2 = 1
# - On day 2, you visit room 1. This is the first day where you have been in all the rooms.
#
# Constraints:
# n == nextVisit.length
# 	2 <= n <= 105
# 	0 <= nextVisit[i] <= i
#
# Helpful references (internal KB):
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
# - Gray code (number, prefix-xor)
#   • When to use: Use when a sequence of binary numbers is needed where successive values differ by only one bit. This is useful for error detection in digital systems or position encoders.
#   • Idea: Gray code is a binary numeral system where two successive values differ in only one bit position. Conversion from a binary number `n` to its Gray code `G(n)` is `n ^ (n >> 1)`, and the inverse operation can also be performed efficiently in O(log N) time.
#   • Invariants: For binary to Gray: The resulting Gray code `G(n)` differs from `n` by exactly one bit for each `n`.; For inverse Gray to binary: The variable `n` accumulates the correct binary value from MSB to LSB.
#   • Tips: Understand the core `n ^ (n >> 1)` transformation for binary to Gray.; The inverse Gray code conversion involves iteratively XORing with right-shifted values.
#   • Pitfalls: Confusing Gray code with standard binary representation.; Incorrectly implementing the iterative inverse transformation logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def firstDayBeenInAllRooms(self, nextVisit):
        """
        :type nextVisit: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nextVisit)
        dp = [0] * n
        
        for i in range(1, n):
            dp[i] = (2 * dp[i - 1] - dp[nextVisit[i - 1]] + 2) % MOD
        
        return dp[-1]