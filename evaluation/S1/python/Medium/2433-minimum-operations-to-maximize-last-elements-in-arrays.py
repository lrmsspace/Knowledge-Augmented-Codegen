# Source: https://leetcode.com/problems/minimum-operations-to-maximize-last-elements-in-arrays/   |   Difficulty: Medium
#
# Problem Description:
# You are given two 0-indexed integer arrays, nums1 and nums2, both having length n.
#
# You are allowed to perform a series of operations (possibly none).
#
# In an operation, you select an index i in the range [0, n - 1] and swap the values of nums1[i] and nums2[i].
#
# Your task is to find the minimum number of operations required to satisfy the following conditions:
#
#
# 	nums1[n - 1] is equal to the maximum value among all elements of nums1, i.e., nums1[n - 1] = max(nums1[0], nums1[1], ..., nums1[n - 1]).
# 	nums2[n - 1] is equal to the maximum value among all elements of nums2, i.e., nums2[n - 1] = max(nums2[0], nums2[1], ..., nums2[n - 1]).
#
#
# Return an integer denoting the minimum number of operations needed to meet both conditions, or -1 if it is impossible to satisfy both conditions.
#
# Example:
# Input: nums1 = [1,2,7], nums2 = [4,5,3]
# Output: 1
# Explanation: In this example, an operation can be performed using index i = 2.
# When nums1[2] and nums2[2] are swapped, nums1 becomes [1,2,3] and nums2 becomes [4,5,7].
# Both conditions are now satisfied.
# It can be shown that the minimum number of operations needed to be performed is 1.
# So, the answer is 1.
#
# Constraints:
# 1 <= n == nums1.length == nums2.length <= 1000
# 	1 <= nums1[i] <= 109
# 	1 <= nums2[i] <= 109
#
# Helpful references (internal KB):
# - Elementary Sorts (array, enumeration)
#   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
#   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
#   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
#   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
#   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOperations(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: int
        """
        n = len(nums1)
        max1, max2 = max(nums1), max(nums2)
        count = 0

        for i in range(n):
            if nums1[i] == max1 and nums2[i] == max2:
                continue
            elif nums1[i] == max1 or nums2[i] == max2:
                count += 1
            else:
                return -1

        return count