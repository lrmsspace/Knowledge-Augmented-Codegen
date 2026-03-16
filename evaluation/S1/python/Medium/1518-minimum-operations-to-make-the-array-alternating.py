# Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums consisting of n positive integers.
#
# The array nums is called alternating if:
#
#
# 	nums[i - 2] == nums[i], where 2 <= i <= n - 1.
# 	nums[i - 1] != nums[i], where 1 <= i <= n - 1.
#
#
# In one operation, you can choose an index i and change nums[i] into any positive integer.
#
# Return the minimum number of operations required to make the array alternating.
#
# Example:
# Input: nums = [3,1,3,2,4,3]
# Output: 3
# Explanation:
# One way to make the array alternating is by converting it to [3,1,3,1,3,1].
# The number of operations required in this case is 3.
# It can be proven that it is not possible to make the array alternating in less than 3 operations.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#
# Helpful references (internal KB):
# - Scheduling jobs on two machines (array, greedy)
#   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
#   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
#   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
#   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
#   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
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
    def minimumOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import Counter

        n = len(nums)

        if n == 1:
            return 0

        even_counts = Counter()
        odd_counts = Counter()

        for i in range(n):
            if i % 2 == 0:
                even_counts[nums[i]] += 1
            else:
                odd_counts[nums[i]] += 1

        even_common = even_counts.most_common(2)
        odd_common = odd_counts.most_common(2)

        even_common.append((None, 0))
        odd_common.append((None, 0))

        if even_common[0][0] != odd_common[0][0]:
            return n - even_common[0][1] - odd_common[0][1]
        else:
            option1 = n - even_common[0][1] - odd_common[1][1]
            option2 = n - even_common[1][1] - odd_common[0][1]
            return min(option1, option2)