# Source: https://leetcode.com/problems/min-max-game/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed integer array nums whose length is a power of 2.
#
# Apply the following algorithm on nums:
#
#
# 	Let n be the length of nums. If n == 1, end the process. Otherwise, create a new 0-indexed integer array newNums of length n / 2.
# 	For every even index i where 0 <= i < n / 2, assign the value of newNums[i] as min(nums[2 * i], nums[2 * i + 1]).
# 	For every odd index i where 0 <= i < n / 2, assign the value of newNums[i] as max(nums[2 * i], nums[2 * i + 1]).
# 	Replace the array nums with newNums.
# 	Repeat the entire process starting from step 1.
#
#
# Return the last number that remains in nums after applying the algorithm.
#
# Example:
# Input: nums = [1,3,5,2,4,8,2,2]
# Output: 1
# Explanation: The following arrays are the results of applying the algorithm repeatedly.
# First: nums = [1,5,4,2]
# Second: nums = [1,4]
# Third: nums = [1]
# 1 is the last remaining number, so we return 1.
#
# Constraints:
# 1 <= nums.length <= 1024
# 	1 <= nums[i] <= 109
# 	nums.length is a power of 2.
#
# Helpful references (internal KB):
# - kth-largest-element-in-an-array (array, merge-sort)
#   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
#   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
#   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
#   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
#   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Sprague-Grundy theorem. Nim (array, number, game-theory, prefix-xor)
#   • When to use: Use when analyzing impartial games with perfect information and no draws, especially to determine winning/losing states or to find a winning strategy. It's particularly useful for games that can be reduced to Nim.
#   • Idea: The Sprague-Grundy theorem states that every impartial game under the normal play convention is equivalent to a Nim pile of a certain size (its nim-value or grundy number). For Nim, a position is a winning position if and only if the XOR sum of all pile sizes is non-zero, allowing for O(N) classification.
#   • Invariants: The XOR sum of the pile sizes (nim-sum) represents the game's current nim-value.; If the nim-sum is zero, any valid move will result in a non-zero nim-sum for the opponent.
#   • Tips: Understand the definition of impartial games and their properties.; Calculate the XOR sum of game components to determine the nim-sum.
#   • Pitfalls: Confusing impartial games with partisan games where players have different moves.; Incorrectly calculating the XOR sum, leading to wrong state classifications.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minMaxGame(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        while len(nums) > 1:
            nums = [min(nums[2*i], nums[2*i+1]) if i % 2 == 0 else max(nums[2*i], nums[2*i+1]) for i in range(len(nums) // 2)]
        return nums[0]