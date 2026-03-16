# Source: https://leetcode.com/problems/maximum-balanced-subsequence-sum/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums.
#
# A subsequence of nums having length k and consisting of indices i0 < i1 < ... < ik-1 is balanced if the following holds:
#
#
# 	nums[ij] - nums[ij-1] >= ij - ij-1, for every j in the range [1, k - 1].
#
#
# A subsequence of nums having length 1 is considered balanced.
#
# Return an integer denoting the maximum possible sum of elements in a balanced subsequence of nums.
#
# A subsequence of an array is a new non-empty array that is formed from the original array by deleting some (possibly none) of the elements without disturbing the relative positions of the remaining elements.
#
# Example:
# Input: nums = [3,3,5,6]
# Output: 14
# Explanation: In this example, the subsequence [3,5,6] consisting of indices 0, 2, and 3 can be selected.
# nums[2] - nums[0] >= 2 - 0.
# nums[3] - nums[2] >= 3 - 2.
# Hence, it is a balanced subsequence, and its sum is the maximum among the balanced subsequences of nums.
# The subsequence consisting of indices 1, 2, and 3 is also valid.
# It can be shown that it is not possible to get a balanced subsequence with a sum greater than 14.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
#   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
#   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
#   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
#   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
#   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
# - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
#   • When to use: Use when selecting a subset of items, each with a weight and value, to maximize total value without exceeding a given capacity. It is applicable for resource allocation problems with discrete choices.
#   • Idea: The Knapsack Problem aims to choose items with maximum total value such that their total weight does not exceed a given capacity. It is typically solved using dynamic programming, achieving a time complexity of O(nW) for n items and capacity W.
#   • Invariants: `dp[j]` (in 1D DP) represents the maximum value achievable with capacity `j` using items considered so far.; When processing item `i` and capacity `j` (decreasing `j`), `dp[j-weight_i]` holds the value from previous items for that reduced capacity.
#   • Tips: Initialize DP table with zeros for capacity 0 and unreachable states.; For 0-1 knapsack with 1D DP, iterate capacity `j` in decreasing order.
#   • Pitfalls: Incorrect iteration order for 1D DP in 0-1 knapsack (using increasing `j`).; Off-by-one errors in item indices or capacity calculations.
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxBalancedSubsequenceSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]
        max_sum = nums[0]

        for i in range(1, n):
            dp[i] = max(dp[i-1] + nums[i], nums[i])
            max_sum = max(max_sum, dp[i])

        return max_sum