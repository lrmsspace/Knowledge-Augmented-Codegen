# Source: https://leetcode.com/problems/split-array-into-maximum-number-of-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums consisting of non-negative integers.
#
# We define the score of subarray nums[l..r] such that l <= r as nums[l] AND nums[l + 1] AND ... AND nums[r] where AND is the bitwise AND operation.
#
# Consider splitting the array into one or more subarrays such that the following conditions are satisfied:
#
#
# 	Each element of the array belongs to exactly one subarray.
# 	The sum of scores of the subarrays is the minimum possible.
#
#
# Return the maximum number of subarrays in a split that satisfies the conditions above.
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [1,0,2,0,1,2]
# Output: 3
# Explanation: We can split the array into the following subarrays:
# - [1,0]. The score of this subarray is 1 AND 0 = 0.
# - [2,0]. The score of this subarray is 2 AND 0 = 0.
# - [1,2]. The score of this subarray is 1 AND 2 = 0.
# The sum of scores is 0 + 0 + 0 = 0, which is the minimum possible score that we can obtain.
# It can be shown that we cannot split the array into more than 3 subarrays with a total score of 0. So we return 3.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 106
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
# - Simulated Annealing (array, number, randomized, simulation)
#   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
#   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
#   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
#   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
#   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxSubarrays(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count = 0
        current_and = (1 << 20) - 1  # 初始化为所有位都是1的数

        for num in nums:
            current_and &= num
            if current_and == 0:
                count += 1
                current_and = (1 << 20) - 1  # 重置为所有位都是1的数

        return count