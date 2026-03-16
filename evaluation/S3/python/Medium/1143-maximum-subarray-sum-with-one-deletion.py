# Source: https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion. In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.
#
# Note that the subarray needs to be non-empty after deleting one element.
#
# Example:
# Input: arr = [1,-2,0,3]
# Output: 4
# Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
#
# Constraints:
# 1 <= arr.length <= 105
# 	-104 <= arr[i] <= 104
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Longest Increasing Subsequence (array, dp-1d)
#   • When to use: When you need to find the maximum length of a subsequence where elements are strictly increasing. It is applicable for problems requiring optimal ordering of non-contiguous elements.
#   • Idea: This DP approach calculates the length of the longest increasing subsequence ending at each position in an array. It builds upon previously computed subsequence lengths, resulting in an O(N^2) time complexity.
#   • Invariants: dp[i] stores the length of the LIS ending at index i.; For any j < i, if A[j] < A[i], then dp[j] + 1 is a candidate length for dp[i].
#   • Tips: Initialize DP array with 1s, as each element itself forms an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling the strict increasing condition (e.g., allowing equality).
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumSum(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        if not arr:
            return 0

        n = len(arr)
        max_end_here = [0] * n
        max_start_here = [0] * n

        max_end_here[0] = arr[0]
        for i in range(1, n):
            max_end_here[i] = max(arr[i], max_end_here[i - 1] + arr[i])

        max_start_here[n - 1] = arr[n - 1]
        for i in range(n - 2, -1, -1):
            max_start_here[i] = max(arr[i], max_start_here[i + 1] + arr[i])

        max_sum = max(max_end_here)  # Case when no deletion is made
        for i in range(1, n - 1):
            max_sum = max(max_sum, max_end_here[i - 1] + max_start_here[i + 1])

        return max_sum