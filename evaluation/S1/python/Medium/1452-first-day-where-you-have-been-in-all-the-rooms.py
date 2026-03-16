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
# - Introduction to Dynamic Programming (array, dp-1d)
#   • When to use: When a problem can be broken down into smaller, overlapping subproblems and an optimal solution to the larger problem can be constructed from optimal solutions to its subproblems. It's suitable for optimizing recursive solutions with repeated computations.
#   • Idea: Dynamic Programming (DP) solves complex problems by breaking them into simpler overlapping subproblems and storing the results to avoid redundant computations. It typically achieves polynomial time complexity, often O(N) or O(N^2) for 1D DP, by trading space for time.
#   • Invariants: dp[i] stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been correctly computed before dp[i] is calculated.
#   • Tips: Clearly define the DP state and its meaning.; Identify the base cases for the recurrence relation.
#   • Pitfalls: Incorrectly defining the DP state or recurrence relation.; Missing or incorrect base cases leading to infinite recursion or wrong results.
# - Josephus Problem (number, dp-1d, recursion)
#   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
#   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
#   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
#   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
#   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
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
        dp[0] = 0  # On day 0, we are in room 0

        for i in range(1, n):
            dp[i] = (2 * dp[i - 1] - dp[nextVisit[i - 1]] + 2) % MOD

        return dp[n - 1]