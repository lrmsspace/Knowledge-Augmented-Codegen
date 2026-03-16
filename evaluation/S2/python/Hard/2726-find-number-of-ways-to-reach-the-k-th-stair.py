# Source: https://leetcode.com/problems/find-number-of-ways-to-reach-the-k-th-stair/   |   Difficulty: Hard
#
# Problem Description:
# You are given a non-negative integer k. There exists a staircase with an infinite number of stairs, with the lowest stair numbered 0.
#
# Alice has an integer jump, with an initial value of 0. She starts on stair 1 and wants to reach stair k using any number of operations. If she is on stair i, in one operation she can:
#
#
# 	Go down to stair i - 1. This operation cannot be used consecutively or on stair 0.
# 	Go up to stair i + 2jump. And then, jump becomes jump + 1.
#
#
# Return the total number of ways Alice can reach stair k.
#
# Note that it is possible that Alice reaches the stair k, and performs some operations to reach the stair k again.
#
# Example:
# Input: k = 0
#
# Output: 2
#
# Explanation:
#
# The 2 possible ways of reaching stair 0 are:
#
#
# 	Alice starts at stair 1.
# 	
# 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
# 	
# 	
# 	Alice starts at stair 1.
# 	
# 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
# 		Using an operation of the second type, she goes up 20 stairs to reach stair 1.
# 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
#
# Constraints:
# 0 <= k <= 109
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
# - Balanced bracket sequences (number, counting)
#   • When to use: Use when the problem asks for the total number of valid arrangements of opening and closing brackets, ensuring all pairs are matched and correctly nested. It applies to combinatorial problems requiring structured pairing.
#   • Idea: This technique counts the number of ways to form sequences of opening and closing brackets such that they are balanced and properly nested. It is a classic combinatorial problem, typically solved in O(N) or O(N^2) time.
#   • Invariants: At any point in sequence construction, the count of open brackets placed must be greater than or equal to the count of closed brackets placed.; The total number of open brackets in a complete valid sequence must exactly equal the total number of closed brackets.
#   • Tips: Recognize the connection to Catalan numbers for common variations (e.g., N pairs of parentheses).; Dynamic programming can solve more complex variations with different bracket types or constraints.
#   • Pitfalls: Forgetting the 'prefix sum' condition: the count of open brackets must always be greater than or equal to close brackets at any point.; Incorrectly applying Catalan numbers to problems with additional constraints or different bracket types.
# - Josephus Problem (number, dp-1d, recursion)
#   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
#   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
#   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
#   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
#   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def waysToReachStair(self, k):
        """
        :type k: int
        :rtype: int
        """
        # The problem can be solved using dynamic programming. We can define a function dp(i, jump) that returns the number of ways to reach stair i with the current jump value. The transitions are as follows:
        # 1. If we go down to stair i - 1, we can only do this if we are not on stair 0 and we cannot do it consecutively. This means we need to check if the last move was not a down move.
        # 2. If we go up to stair i + 2jump, we will increase the jump value by 1 for the next move.
        #
        # We can use memoization to store previously computed results for dp(i, jump) to avoid redundant calculations.
        #
        # The base case is when i == k, in which case there is one way to reach stair k (by being on it). If i > k, there are no ways to reach stair k from there.
        #
        # The final answer will be dp(1, 0) since Alice starts on stair 1 with an initial jump of 0.

        from functools import lru_cache

        @lru_cache(maxsize=None)
        def dp(i, jump):
            if i == k:
                return 1
            if i > k:
                return 0
            
            ways = 0
            
            # Move down
            if i > 0 and (i - 1 != i):  # Ensure not consecutive down moves
                ways += dp(i - 1, jump)
            
            # Move up
            ways += dp(i + 2 * jump, jump + 1)
            
            return ways
        
        return dp(1, 0)