# Source: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/   |   Difficulty: Medium
#
# Problem Description:
# Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
#
# Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
#
# The tests are generated such that there is exactly one solution. You may not use the same element twice.
#
# Your solution must use only constant extra space.
#
# Example:
# Input: numbers = [2,7,11,15], target = 9
# Output: [1,2]
# Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
#
# Constraints:
# 2 <= numbers.length <= 3 * 104
# 	-1000 <= numbers[i] <= 1000
# 	numbers is sorted in non-decreasing order.
# 	-1000 <= target <= 1000
# 	The tests are generated such that there is exactly one solution.
#
# Helpful references (internal KB):
# - Binary search (interval, number, binary-search-answer, enumeration)
#   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
#   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
#   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
#   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
#   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
#   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
#   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
#   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
#   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def twoSum(self, numbers, target):
        """
        :type numbers: List[int]
        :type target: int
        :rtype: List[int]
        """
        # 双指针
        left, right = 0, len(numbers) - 1

        while left < right:
            current_sum = numbers[left] + numbers[right]

            if current_sum == target:
                return [left + 1, right + 1]  # 返回 1-indexed 的结果
            elif current_sum < target:
                left += 1  # 增大左指针以增加总和
            else:
                right -= 1  # 减小右指针以减少总和

        return []  # 根据题意，这行永远不会被执行，因为保证有唯一解