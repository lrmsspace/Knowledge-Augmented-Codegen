# Source: https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n matrix mat that has its rows sorted in non-decreasing order and an integer k.
#
# You are allowed to choose exactly one element from each row to form an array.
#
# Return the kth smallest array sum among all possible arrays.
#
# Example:
# Input: mat = [[1,3,11],[2,4,6]], k = 5
# Output: 7
# Explanation: Choosing one element from each row, the first k smallest sum are:
# [1,2], [1,4], [3,2], [3,4], [1,6]. Where the 5th sum is 7.
#
# Constraints:
# m == mat.length
# 	n == mat.length[i]
# 	1 <= m, n <= 40
# 	1 <= mat[i][j] <= 5000
# 	1 <= k <= min(200, nm)
# 	mat[i] is a non-decreasing array.
#
# Helpful references (internal KB):
# - kth-largest-element-in-an-array (heap, array, heap-select)
#   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
#   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
#   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
#   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
#   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def kthSmallest(self, mat, k):
        """
        :type mat: List[List[int]]
        :type k: int
        :rtype: int
        """
        import heapq
        m, n = len(mat), len(mat[0])
        min_heap = [(sum(row[0] for row in mat), [0] * m)]
        for _ in range(k - 1):
            current_sum, indices = heapq.heappop(min_heap)
            for i in range(m):
                if indices[i] + 1 < n:
                    new_indices = indices[:]
                    new_indices[i] += 1
                    new_sum = current_sum - mat[i][indices[i]] + mat[i][new_indices[i]]
                    heapq.heappush(min_heap, (new_sum, new_indices))
        return min_heap[0][0]