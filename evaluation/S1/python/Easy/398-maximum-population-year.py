# Source: https://leetcode.com/problems/maximum-population-year/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 2D integer array logs where each logs[i] = [birthi, deathi] indicates the birth and death years of the ith person.
#
# The population of some year x is the number of people alive during that year. The ith person is counted in year x's population if x is in the inclusive range [birthi, deathi - 1]. Note that the person is not counted in the year that they die.
#
# Return the earliest year with the maximum population.
#
# Example:
# Input: logs = [[1993,1999],[2000,2010]]
# Output: 1993
# Explanation: The maximum population is 1, and 1993 is the earliest year with this population.
#
# Constraints:
# 1 <= logs.length <= 100
# 	1950 <= birthi < deathi <= 2050
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Fenwick Tree (array, bit-fenwick, prefix-sum)
#   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
#   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
#   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
#   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
#   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumPopulation(self, logs):
        """
        :type logs: List[List[int]]
        :rtype: int
        """
        year_count = [0] * 101  # Index 0 corresponds to year 1950

        for birth, death in logs:
            year_count[birth - 1950] += 1
            year_count[death - 1950] -= 1

        max_population = 0
        current_population = 0
        earliest_year = 1950

        for year in range(101):
            current_population += year_count[year]
            if current_population > max_population:
                max_population = current_population
                earliest_year = 1950 + year

        return earliest_year