# Source: https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums of length n. The number of ways to partition nums is the number of pivot indices that satisfy both conditions:
#
#
# 	1 <= pivot < n
# 	nums[0] + nums[1] + ... + nums[pivot - 1] == nums[pivot] + nums[pivot + 1] + ... + nums[n - 1]
#
#
# You are also given an integer k. You can choose to change the value of one element of nums to k, or to leave the array unchanged.
#
# Return the maximum possible number of ways to partition nums to satisfy both conditions after changing at most one element.
#
# Example:
# Input: nums = [2,-1,2], k = 3
# Output: 1
# Explanation: One optimal approach is to change nums[0] to k. The array becomes [3,-1,2].
# There is one way to partition the array:
# - For pivot = 2, we have the partition [3,-1 | 2]: 3 + -1 == 2.
#
# Constraints:
# n == nums.length
# 	2 <= n <= 105
# 	-105 <= k, nums[i] <= 105
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Fenwick Tree (array, bit-fenwick, prefix-sum)
#   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
#   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
#   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
#   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
#   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def waysToPartition(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        total_sum = sum(nums)
        prefix_sum = 0
        count = 0
        prefix_count = {}
        suffix_count = {}

        # Count the number of ways to partition without any changes
        for i in range(n - 1):
            prefix_sum += nums[i]
            suffix_sum = total_sum - prefix_sum
            if prefix_sum == suffix_sum:
                count += 1
            prefix_count[prefix_sum] = prefix_count.get(prefix_sum, 0) + 1

        # Check the effect of changing each element to k
        for i in range(n):
            original_value = nums[i]
            new_value = k
            diff = new_value - original_value

            # Calculate new total sum after change
            new_total_sum = total_sum + diff

            # Check if we can partition with the new total sum
            if (new_total_sum % 2 == 0):
                half_sum = new_total_sum // 2

                # Check if we can achieve half_sum with the prefix or suffix counts
                if half_sum in prefix_count:
                    count = max(count, prefix_count[half_sum])
                if half_sum - diff in suffix_count:
                    count = max(count, suffix_count[half_sum - diff])

            # Update suffix counts for the next iteration
            if i < n - 1:
                suffix_count[total_sum - prefix_sum] = suffix_count.get(total_sum - prefix_sum, 0) + 1

        return count