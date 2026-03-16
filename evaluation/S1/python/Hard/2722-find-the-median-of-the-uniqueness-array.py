# Source: https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums. The uniqueness array of nums is the sorted array that contains the number of distinct elements of all the subarrays of nums. In other words, it is a sorted array consisting of distinct(nums[i..j]), for all 0 <= i <= j < nums.length.
#
# Here, distinct(nums[i..j]) denotes the number of distinct elements in the subarray that starts at index i and ends at index j.
#
# Return the median of the uniqueness array of nums.
#
# Note that the median of an array is defined as the middle element of the array when it is sorted in non-decreasing order. If there are two choices for a median, the smaller of the two values is taken.
#
# Example:
# Input: nums = [1,2,3]
#
# Output: 1
#
# Explanation:
#
# The uniqueness array of nums is [distinct(nums[0..0]), distinct(nums[1..1]), distinct(nums[2..2]), distinct(nums[0..1]), distinct(nums[1..2]), distinct(nums[0..2])] which is equal to [1, 1, 1, 2, 2, 3]. The uniqueness array has a median of 1. Therefore, the answer is 1.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - MEX (minimal excluded) of a sequence (tree, binary-search)
#   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
#   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
#   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
#   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
#   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
# -  
# Kth order statistic in O(N) (array, quickselect)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without fully sorting the entire data structure. It's particularly useful for large datasets where a full sort is too slow.
#   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list. It uses a divide-and-conquer approach similar to Quicksort, but only recurses on one side, achieving an average time complexity of O(N).
#   • Invariants: All elements to the left of the pivot are less than or equal to the pivot's value.; All elements to the right of the pivot are greater than or equal to the pivot's value.
#   • Tips: Choose a good pivot strategy, such as a random pivot, to minimize the chance of worst-case performance.; Handle duplicate elements carefully during the partitioning step to ensure correctness.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Deep recursion without tail call optimization can cause stack overflow errors.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def medianOfUniquenessArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # Step 1: Calculate the number of distinct elements in all subarrays
        n = len(nums)
        distinct_counts = []
        for i in range(n):
            seen = set()
            for j in range(i, n):
                seen.add(nums[j])
                distinct_counts.append(len(seen))

        # Step 2: Sort the distinct counts and find the median
        distinct_counts.sort()
        m = len(distinct_counts)
        if m % 2 == 1:
            return distinct_counts[m // 2]
        else:
            return distinct_counts[m // 2 - 1]