# Source: https://leetcode.com/problems/find-the-value-of-the-partition/   |   Difficulty: Medium
#
# Problem Description:
# You are given a positive integer array nums.
#
# Partition nums into two arrays, nums1 and nums2, such that:
#
#
# 	Each element of the array nums belongs to either the array nums1 or the array nums2.
# 	Both arrays are non-empty.
# 	The value of the partition is minimized.
#
#
# The value of the partition is |max(nums1) - min(nums2)|.
#
# Here, max(nums1) denotes the maximum element of the array nums1, and min(nums2) denotes the minimum element of the array nums2.
#
# Return the integer denoting the value of such partition.
#
# Example:
# Input: nums = [1,3,2,4]
# Output: 1
# Explanation: We can partition the array nums into nums1 = [1,2] and nums2 = [3,4].
# - The maximum element of the array nums1 is equal to 2.
# - The minimum element of the array nums2 is equal to 3.
# The value of the partition is |2 - 3| = 1. 
# It can be proven that 1 is the minimum value out of all partitions.
#
# Constraints:
# 2 <= nums.length <= 105
# 	1 <= nums[i] <= 109
#
# Helpful references (internal KB):
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
# -  
# Kth order statistic in O(N) (array, quickselect, randomized)
#   • When to use: When you need to efficiently find the Kth smallest or largest element in an unsorted array. It is ideal when a full sort is unnecessary and average linear time performance is acceptable.
#   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list by repeatedly partitioning the array around a pivot. It achieves an average time complexity of O(N) and a worst-case complexity of O(N^2).
#   • Invariants: All elements in the left partition are less than or equal to the pivot element.; All elements in the right partition are greater than or equal to the pivot element.
#   • Tips: Shuffle the input array or choose a random pivot to achieve average O(N) performance.; The algorithm modifies the input array in place, so a copy might be needed if the original must be preserved.
#   • Pitfalls: A consistently bad pivot choice (e.g., always smallest/largest) leads to O(N^2) worst-case time.; Not suitable if the relative order of other elements needs to be preserved (it's not a stable algorithm).
# - Range Minimum Query (array, sparse-table)
#   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
#   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
#   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
#   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
#   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findValueOfPartition(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        min_diff = float('inf')
        for i in range(1, len(nums)):
            min_diff = min(min_diff, nums[i] - nums[i - 1])
        return min_diff