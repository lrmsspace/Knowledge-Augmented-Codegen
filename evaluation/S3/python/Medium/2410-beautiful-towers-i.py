# Source: https://leetcode.com/problems/beautiful-towers-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array heights of n integers representing the number of bricks in n consecutive towers. Your task is to remove some bricks to form a mountain-shaped tower arrangement. In this arrangement, the tower heights are non-decreasing, reaching a maximum peak value with one or multiple consecutive towers and then non-increasing.
#
# Return the maximum possible sum of heights of a mountain-shaped tower arrangement.
#
# Example:
# Input: heights = [5,3,4,1,1]
#
# Output: 13
#
# Explanation:
#
# We remove some bricks to make heights = [5,3,3,1,1], the peak is at index 0.
#
# Constraints:
# 1 <= n == heights.length <= 103
# 	1 <= heights[i] <= 109
#
# Helpful references (internal KB):
# - Convex hull trick and Li Chao tree (array, number, dp-1d)
#   • When to use: Use when the optimal solution for a subproblem depends only on solutions to smaller, contiguous subproblems. It's effective for optimizing sequential decision-making or finding optimal values in arrays.
#   • Idea: Dynamic Programming 1D solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. It typically achieves O(N) or O(N log N) time and O(N) or O(1) space complexity.
#   • Invariants: dp[i] correctly stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been computed and are correct.
#   • Tips: Clearly define the state: what does dp[i] represent for the subproblem?; Establish correct base cases for the smallest subproblems.
#   • Pitfalls: Incorrectly defining the state or recurrence relation.; Missing or incorrect base cases, leading to incorrect results.
# - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
#   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
#   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
#   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
#   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
#   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
# - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
#   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
#   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
#   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
#   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumSumOfHeights(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        n = len(heights)
        left = [0] * n
        right = [0] * n

        # Calculate the longest non-decreasing subsequence from the left
        for i in range(n):
            left[i] = heights[i]
            for j in range(i):
                if heights[j] <= heights[i]:
                    left[i] = max(left[i], left[j] + heights[i])

        # Calculate the longest non-increasing subsequence from the right
        for i in range(n - 1, -1, -1):
            right[i] = heights[i]
            for j in range(i + 1, n):
                if heights[j] <= heights[i]:
                    right[i] = max(right[i], right[j] + heights[i])

        # Find the maximum sum of heights of a mountain-shaped tower arrangement
        max_sum = 0
        for i in range(n):
            max_sum = max(max_sum, left[i] + right[i] - heights[i])

        return max_sum