# Source: https://leetcode.com/problems/minimum-cost-good-caption/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string caption of length n. A good caption is a string where every character appears in groups of at least 3 consecutive occurrences.
#
# For example:
#
#
# 	"aaabbb" and "aaaaccc" are good captions.
# 	"aabbb" and "ccccd" are not good captions.
#
#
# You can perform the following operation any number of times:
#
# Choose an index i (where 0 <= i < n) and change the character at that index to either:
#
#
# 	The character immediately before it in the alphabet (if caption[i] != 'a').
# 	The character immediately after it in the alphabet (if caption[i] != 'z').
#
#
# Your task is to convert the given caption into a good caption using the minimum number of operations, and return it. If there are multiple possible good captions, return the lexicographically smallest one among them. If it is impossible to create a good caption, return an empty string "".
#
# Example:
# Input: caption = "cdcd"
#
# Output: "cccc"
#
# Explanation:
#
# It can be shown that the given caption cannot be transformed into a good caption with fewer than 2 operations. The possible good captions that can be created using exactly 2 operations are:
#
#
# 	"dddd": Change caption[0] and caption[2] to their next character 'd'.
# 	"cccc": Change caption[1] and caption[3] to their previous character 'c'.
#
#
# Since "cccc" is lexicographically smaller than "dddd", return "cccc".
#
# Constraints:
# 1 <= caption.length <= 5 * 104
# 	caption consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - interval-dp (array, interval-dp)
#   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
#   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
#   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
#   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
# - Knuth's Optimization (array, interval, dp-2d)
#   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
#   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
#   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minCostGoodCaption(self, caption):
        """
        :type caption: str
        :rtype: str
        """
        n = len(caption)
        s = caption + caption  # Duplicate the string to handle circular cases
        dp = [[float('inf')] * (2 * n) for _ in range(2 * n)]

        # Base case: single characters
        for i in range(2 * n):
            dp[i][i] = 0

        # Fill the DP table
        for length in range(2, n + 1):  # Length of the interval
            for l in range(0, 2 * n - length + 1):
                r = l + length - 1
                if s[l] == s[r]:
                    dp[l][r] = dp[l + 1][r - 1]
                else:
                    dp[l][r] = min(dp[l + 1][r], dp[l][r - 1]) + 1

        # Find the minimum cost for a good caption of length n
        min_cost = float('inf')
        best_caption = None
        for start in range(n):
            cost = dp[start][start + n - 1]
            if cost < min_cost:
                min_cost = cost
                best_caption = s[start:start + n]

        return best_caption