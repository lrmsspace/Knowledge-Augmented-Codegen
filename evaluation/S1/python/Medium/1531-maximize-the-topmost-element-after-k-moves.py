# Source: https://leetcode.com/problems/maximize-the-topmost-element-after-k-moves/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums representing the contents of a pile, where nums[0] is the topmost element of the pile.
#
# In one move, you can perform either of the following:
#
#
# 	If the pile is not empty, remove the topmost element of the pile.
# 	If there are one or more removed elements, add any one of them back onto the pile. This element becomes the new topmost element.
#
#
# You are also given an integer k, which denotes the total number of moves to be made.
#
# Return the maximum value of the topmost element of the pile possible after exactly k moves. In case it is not possible to obtain a non-empty pile after k moves, return -1.
#
# Example:
# Input: nums = [5,2,2,4,0,6], k = 4
# Output: 5
# Explanation:
# One of the ways we can end with 5 at the top of the pile after 4 moves is as follows:
# - Step 1: Remove the topmost element = 5. The pile becomes [2,2,4,0,6].
# - Step 2: Remove the topmost element = 2. The pile becomes [2,4,0,6].
# - Step 3: Remove the topmost element = 2. The pile becomes [4,0,6].
# - Step 4: Add 5 back onto the pile. The pile becomes [5,4,0,6].
# Note that this is not the only way to end with 5 at the top of the pile. It can be shown that 5 is the largest answer possible after 4 moves.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i], k <= 109
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Minimum stack / Minimum queue (queue, stack, simulation)
#   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
#   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
#   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
#   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
#   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
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
    def maximumTop(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        if n == 1:
            return -1 if k % 2 == 1 else nums[0]
        
        if k == 0:
            return nums[0]
        
        if k == 1:
            return nums[1] if n > 1 else -1
        
        max_elem = -1
        if k - 1 < n:
            max_elem = max(nums[:k-1])
        else:
            max_elem = max(nums)
        
        if k < n:
            max_elem = max(max_elem, nums[k])
        
        return max_elem