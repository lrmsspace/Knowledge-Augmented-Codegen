# Source: https://leetcode.com/problems/peak-index-in-a-mountain-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer mountain array arr of length n where the values increase to a peak element and then decrease.
#
# Return the index of the peak element.
#
# Your task is to solve it in O(log(n)) time complexity.
#
# Example:
# Input: arr = [0,1,0]
#
# Output: 1
#
# Constraints:
# 3 <= arr.length <= 105
# 	0 <= arr[i] <= 106
# 	arr is guaranteed to be a mountain array.
#
# Helpful references (internal KB):
# - Ternary Search (number, binary-search)
#   • When to use: Use when searching for the minimum or maximum of a unimodal function over a continuous interval. It efficiently narrows down the search space by evaluating the function at two internal points.
#   • Idea: Ternary search is an optimization algorithm for finding the extremum (minimum or maximum) of a unimodal function within a given interval. It repeatedly reduces the search interval by two-thirds, achieving logarithmic time complexity with respect to the interval size.
#   • Invariants: The global extremum of the unimodal function within the initial range is always contained within the current interval [L, R].; The interval [L, R] is non-empty and its length strictly decreases in each iteration.
#   • Tips: Carefully define the search interval [L, R] for the function.; Choose two internal points, typically L + (R-L)/3 and R - (R-L)/3.
#   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Floating-point precision issues can lead to infinite loops or incorrect bounds.
# - Ternary Search (interval, number, binary-search)
#   • When to use: Use when finding the extremum (maximum or minimum) of a unimodal function over a continuous interval, where the function strictly increases then decreases, or vice versa.
#   • Idea: Ternary search is an optimization algorithm that efficiently finds the extremum (maximum or minimum) of a unimodal function over a continuous interval. It operates in logarithmic time, O(log N), by repeatedly narrowing the search space.
#   • Invariants: The global extremum of the unimodal function is always contained within the current interval [l, r].; The function f(x) remains unimodal on the interval [l, r] throughout the search process.
#   • Tips: For floating-point functions, use a fixed number of iterations (e.g., 100-300) instead of an epsilon threshold for robustness.; The two comparison points m1 and m2 should divide the interval into three roughly equal parts for optimal convergence.
#   • Pitfalls: Applying ternary search to a non-unimodal function will not guarantee finding the global extremum.; Floating-point precision errors can lead to incorrect comparisons or infinite loops if epsilon is too small.
# - Ternary Search (interval, number, binary-search, greedy)
#   • When to use: Use when searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It efficiently narrows down the search space by evaluating the function at two internal points.
#   • Idea: Ternary search is a divide and conquer algorithm that finds the extremum of a unimodal function within an interval by repeatedly reducing the search space by approximately one-third. It has a logarithmic time complexity, similar to binary search, but requires two function evaluations per step.
#   • Invariants: The extremum of the unimodal function lies within the current interval [l, r].; The function value at m1 is compared with the function value at m2.
#   • Tips: Handle discrete intervals by checking remaining points when interval size is small.; Consider Golden Section Search to reduce function evaluations per iteration.
#   • Pitfalls: Incorrectly applying to non-unimodal functions.; Infinite loops if stopping condition for discrete intervals is not handled.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def peakIndexInMountainArray(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        left, right = 0, len(arr) - 1
        
        while left < right:
            mid = left + (right - left) // 2
            
            if arr[mid] < arr[mid + 1]:
                left = mid + 1
            else:
                right = mid
        
        return left