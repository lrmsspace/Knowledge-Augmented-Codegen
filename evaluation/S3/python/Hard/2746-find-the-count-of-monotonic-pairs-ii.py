# Source: https://leetcode.com/problems/find-the-count-of-monotonic-pairs-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of positive integers nums of length n.
#
# We call a pair of non-negative integer arrays (arr1, arr2) monotonic if:
#
#
# 	The lengths of both arrays are n.
# 	arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <= ... <= arr1[n - 1].
# 	arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >= ... >= arr2[n - 1].
# 	arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
#
#
# Return the count of monotonic pairs.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [2,3,2]
#
# Output: 4
#
# Explanation:
#
# The good pairs are:
#
#
# 	([0, 1, 1], [2, 2, 1])
# 	([0, 1, 2], [2, 2, 0])
# 	([0, 2, 2], [2, 1, 0])
# 	([1, 2, 2], [1, 1, 0])
#
# Constraints:
# 1 <= n == nums.length <= 2000
# 	1 <= nums[i] <= 1000
#
# Helpful references (internal KB):
# - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
#   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
#   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
#   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
#   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
#   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
# - Placing Bishops on a Chessboard (array, counting, dp-2d)
#   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
#   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
#   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
#   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
#   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
# - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
#   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
#   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
#   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
#   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
#   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countOfPairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)

        # dp[i][j] will store the count of ways to fill arr1 and arr2 up to index i with arr1[i] = j
        dp = [[0] * 1001 for _ in range(n)]
        
        # Base case: for the first element, we can choose arr1[0] from 0 to nums[0]
        for j in range(nums[0] + 1):
            dp[0][j] = 1

        for i in range(1, n):
            # Prefix sums for dp[i-1] to quickly calculate counts
            prefix_sum = [0] * 1002
            for j in range(1001):
                prefix_sum[j + 1] = (prefix_sum[j] + dp[i - 1][j]) % MOD
            
            for j in range(nums[i] + 1):
                # arr2[i] = nums[i] - arr1[i], so arr2[i] >= arr2[i-1]
                # This means arr1[i] <= arr1[i-1]
                if j <= nums[i]:
                    dp[i][j] = prefix_sum[j + 1]

        return sum(dp[n - 1]) % MOD