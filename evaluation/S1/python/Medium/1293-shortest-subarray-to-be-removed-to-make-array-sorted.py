# Source: https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining elements in arr are non-decreasing.
#
# Return the length of the shortest subarray to remove.
#
# A subarray is a contiguous subsequence of the array.
#
# Example:
# Input: arr = [1,2,3,10,4,2,3,5]
# Output: 3
# Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.
# Another correct solution is to remove the subarray [3,10,4].
#
# Constraints:
# 1 <= arr.length <= 105
# 	0 <= arr[i] <= 109
#
# Helpful references (internal KB):
# - Suffix array (array, string, suffix-array, binary-search)
#   • When to use: Use suffix arrays for efficient string processing tasks like finding all occurrences of a pattern, locating the longest common substring, or performing various substring queries. It provides a sorted index of all suffixes.
#   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices in lexicographical order. It enables various string operations to be performed efficiently, often with O(N log N) or O(N) time complexity for construction and O(M log N) or O(M) for queries.
#   • Invariants: The suffix array A always contains N elements, where N is the length of the original string.; For any valid index i, A[i] stores a starting position within the original string S.
#   • Tips: Append a unique sentinel character (e.g., '$') to the string to ensure all suffixes are distinct.; Combine with a Longest Common Prefix (LCP) array for enhanced functionality, such as counting distinct substrings.
#   • Pitfalls: Naive construction by sorting all suffixes directly is inefficient (O(N^2 log N) or worse).; Implementing advanced construction algorithms from scratch can be complex and error-prone.
# - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
#   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
#   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
#   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
#   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
#   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
# - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
#   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
#   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
#   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
#   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
#   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findLengthOfShortestSubarray(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        left = 0
        while left + 1 < n and arr[left] <= arr[left + 1]:
            left += 1

        if left == n - 1:
            return 0

        right = n - 1
        while right - 1 >= 0 and arr[right - 1] <= arr[right]:
            right -= 1

        res = min(n - left - 1, right)

        i = 0
        j = right
        while i <= left and j < n:
            if arr[i] <= arr[j]:
                res = min(res, j - i - 1)
                i += 1
            else:
                j += 1

        return res