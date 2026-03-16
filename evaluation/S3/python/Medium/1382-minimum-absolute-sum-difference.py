# Source: https://leetcode.com/problems/minimum-absolute-sum-difference/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive integer arrays nums1 and nums2, both of length n.
#
# The absolute sum difference of arrays nums1 and nums2 is defined as the sum of |nums1[i] - nums2[i]| for each 0 <= i < n (0-indexed).
#
# You can replace at most one element of nums1 with any other element in nums1 to minimize the absolute sum difference.
#
# Return the minimum absolute sum difference after replacing at most one element in the array nums1. Since the answer may be large, return it modulo 109 + 7.
#
# |x| is defined as:
#
#
# 	x if x >= 0, or
# 	-x if x < 0.
#
# Example:
# Input: nums1 = [1,7,5], nums2 = [2,3,5]
# Output: 3
# Explanation: There are two possible optimal solutions:
# - Replace the second element with the first: [1,7,5] => [1,1,5], or
# - Replace the second element with the third: [1,7,5] => [1,5,5].
# Both will yield an absolute sum difference of |1-2| + (|1-3| or |5-3|) + |5-5| = 3.
#
# Constraints:
# n == nums1.length
# 	n == nums2.length
# 	1 <= n <= 105
# 	1 <= nums1[i], nums2[i] <= 105
#
# Helpful references (internal KB):
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
# - Elementary Sorts (array, enumeration)
#   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
#   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
#   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
#   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
#   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minAbsoluteSumDiff(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        mod = 10**9 + 7
        n = len(nums1)
        sorted_nums1 = sorted(nums1)
        total_diff = 0
        max_reduction = 0

        for i in range(n):
            diff = abs(nums1[i] - nums2[i])
            total_diff = (total_diff + diff) % mod

            # Binary search to find the closest element in sorted_nums1 to nums2[i]
            idx = self.binary_search(sorted_nums1, nums2[i])
            if idx < n:
                max_reduction = max(max_reduction, diff - abs(sorted_nums1[idx] - nums2[i]))
            if idx > 0:
                max_reduction = max(max_reduction, diff - abs(sorted_nums1[idx-1] - nums2[i]))

        return (total_diff - max_reduction) % mod