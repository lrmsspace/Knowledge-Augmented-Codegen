# Source: https://leetcode.com/problems/find-the-largest-almost-missing-integer/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums and an integer k.
#
# An integer x is almost missing from nums if x appears in exactly one subarray of size k within nums.
#
# Return the largest almost missing integer from nums. If no such integer exists, return -1.
# A subarray is a contiguous sequence of elements within an array.
#
# Example:
# Input: nums = [3,9,2,1,7], k = 3
#
# Output: 7
#
# Explanation:
#
#
# 	1 appears in 2 subarrays of size 3: [9, 2, 1] and [2, 1, 7].
# 	2 appears in 3 subarrays of size 3: [3, 9, 2], [9, 2, 1], [2, 1, 7].
# 	3 appears in 1 subarray of size 3: [3, 9, 2].
# 	7 appears in 1 subarray of size 3: [2, 1, 7].
# 	9 appears in 2 subarrays of size 3: [3, 9, 2], and [9, 2, 1].
#
#
# We return 7 since it is the largest integer that appears in exactly one subarray of size k.
#
# Constraints:
# 1 <= nums.length <= 50
# 	0 <= nums[i] <= 50
# 	1 <= k <= nums.length
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
# - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
#   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
#   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
#   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
#   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
#   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def largestInteger(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        n = len(nums)
        count_map = defaultdict(int)

        # Count occurrences of each integer in all subarrays of size k
        for i in range(n - k + 1):
            subarray = nums[i:i + k]
            unique_integers = set(subarray)
            for num in unique_integers:
                count_map[num] += 1

        # Find the largest integer that appears in exactly one subarray of size k
        largest_almost_missing = -1
        for num, count in count_map.items():
            if count == 1:
                largest_almost_missing = max(largest_almost_missing, num)

        return largest_almost_missing