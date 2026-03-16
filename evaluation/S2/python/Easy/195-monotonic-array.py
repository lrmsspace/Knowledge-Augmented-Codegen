# Source: https://leetcode.com/problems/monotonic-array/   |   Difficulty: Easy
#
# Problem Description:
# An array is monotonic if it is either monotone increasing or monotone decreasing.
#
# An array nums is monotone increasing if for all i <= j, nums[i] <= nums[j]. An array nums is monotone decreasing if for all i <= j, nums[i] >= nums[j].
#
# Given an integer array nums, return true if the given array is monotonic, or false otherwise.
#
# Example:
# Input: nums = [1,2,2,3]
# Output: true
#
# Constraints:
# 1 <= nums.length <= 105
# 	-105 <= nums[i] <= 105
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - Convex Hull construction (geometry, array, stack, sweep-line, monotonic-stack)
#   • When to use: When you need to find the smallest convex polygon enclosing a given set of points. It's used for problems requiring the outermost boundary of a point set.
#   • Idea: Convex Hull construction algorithms, like Graham Scan or Monotone Chain, find the smallest convex polygon that encloses a given set of points. These algorithms typically have a time complexity of O(N log N) due to sorting.
#   • Invariants: The points currently on the stack form a convex chain in the desired direction.; For any three consecutive points A, B, C on the stack, the turn from AB to BC maintains convexity.
#   • Tips: Use an orientation test (cross product) to determine if points make a clockwise or counter-clockwise turn.; Handle collinear points carefully, especially if they need to be included in the hull.
#   • Pitfalls: Incorrectly handling collinear points can lead to an incomplete or incorrect hull.; Floating-point precision issues can affect orientation tests, leading to wrong turns.
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
    def isMonotonic(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        increasing = decreasing = True
        
        for i in range(1, len(nums)):
            if nums[i] > nums[i - 1]:
                decreasing = False
            elif nums[i] < nums[i - 1]:
                increasing = False
            
            if not increasing and not decreasing:
                return False
        
        return True