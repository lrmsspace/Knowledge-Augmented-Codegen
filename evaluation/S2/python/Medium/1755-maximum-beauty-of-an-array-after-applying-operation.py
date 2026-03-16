# Source: https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums and a non-negative integer k.
#
# In one operation, you can do the following:
#
#
# 	Choose an index i that hasn't been chosen before from the range [0, nums.length - 1].
# 	Replace nums[i] with any integer from the range [nums[i] - k, nums[i] + k].
#
#
# The beauty of the array is the length of the longest subsequence consisting of equal elements.
#
# Return the maximum possible beauty of the array nums after applying the operation any number of times.
#
# Note that you can apply the operation to each index only once.
#
# A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the order of the remaining elements.
#
# Example:
# Input: nums = [4,6,1,2], k = 2
# Output: 3
# Explanation: In this example, we apply the following operations:
# - Choose index 1, replace it with 4 (from range [4,8]), nums = [4,4,1,2].
# - Choose index 3, replace it with 4 (from range [0,4]), nums = [4,4,1,4].
# After the applied operations, the beauty of the array nums is 3 (subsequence consisting of indices 0, 1, and 3).
# It can be proven that 3 is the maximum possible length we can achieve.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i], k <= 105
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
#   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
#   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
#   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
#   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
#   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
# -  
# Kth order statistic in O(N) (array, enumeration)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
#   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
#   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
#   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumBeauty(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import Counter
        count = Counter(nums)
        max_beauty = 0

        for num in count:
            current_beauty = count[num]
            for other_num in count:
                if abs(num - other_num) <= k:
                    current_beauty += count[other_num]
            max_beauty = max(max_beauty, current_beauty)

        return max_beauty