# Source: https://leetcode.com/problems/minimum-levels-to-gain-more-points/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary array possible of length n.
#
# Alice and Bob are playing a game that consists of n levels. Some of the levels in the game are impossible to clear while others can always be cleared. In particular, if possible[i] == 0, then the ith level is impossible to clear for both the players. A player gains 1 point on clearing a level and loses 1 point if the player fails to clear it.
#
# At the start of the game, Alice will play some levels in the given order starting from the 0th level, after which Bob will play for the rest of the levels.
#
# Alice wants to know the minimum number of levels she should play to gain more points than Bob, if both players play optimally to maximize their points.
#
# Return the minimum number of levels Alice should play to gain more points. If this is not possible, return -1.
#
# Note that each player must play at least 1 level.
#
# Example:
# Input: possible = [1,0,1,0]
#
# Output: 1
#
# Explanation:
#
# Let's look at all the levels that Alice can play up to:
#
#
# 	If Alice plays only level 0 and Bob plays the rest of the levels, Alice has 1 point, while Bob has -1 + 1 - 1 = -1 point.
# 	If Alice plays till level 1 and Bob plays the rest of the levels, Alice has 1 - 1 = 0 points, while Bob has 1 - 1 = 0 points.
# 	If Alice plays till level 2 and Bob plays the rest of the levels, Alice has 1 - 1 + 1 = 1 point, while Bob has -1 point.
#
#
# Alice must play a minimum of 1 level to gain more points.
#
# Constraints:
# 2 <= n == possible.length <= 105
# 	possible[i] is either 0 or 1.
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumLevels(self, possible):
        """
        :type possible: List[int]
        :rtype: int
        """
        n = len(possible)
        total_points = sum(1 if x == 1 else -1 for x in possible)
        
        alice_points = 0
        bob_points = total_points
        
        for i in range(n - 1):
            if possible[i] == 1:
                alice_points += 1
            else:
                alice_points -= 1
            
            if possible[i] == 1:
                bob_points -= 1
            else:
                bob_points += 1
            
            if alice_points > bob_points:
                return i + 1
        
        return -1