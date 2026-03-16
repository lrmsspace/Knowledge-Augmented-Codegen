# Source: https://leetcode.com/problems/sort-colors/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
#
# We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
#
# You must solve this problem without using the library's sort function.
#
# Example:
# Input: nums = [2,0,2,1,1,0]
# Output: [0,0,1,1,2,2]
#
# Constraints:
# n == nums.length
# 	1 <= n <= 300
# 	nums[i] is either 0, 1, or 2.
#
#
#  
# Follow up: Could you come up with a one-pass algorithm using only constant extra space?
#
# Helpful references (internal KB):
# - Quicksort (array, two-pointers, randomized)
#   • When to use: Use Quicksort for efficient in-place sorting of arrays, especially when average-case performance and cache efficiency are prioritized. It is suitable for large datasets where memory usage is a concern.
#   • Idea: Quicksort is a divide-and-conquer sorting algorithm that partitions an array around a pivot element, then recursively sorts the two resulting subarrays. Its average time complexity is O(N log N), but can degrade to O(N^2) in the worst case.
#   • Invariants: All elements to the left of the `lt` pointer are less than the pivot value.; All elements to the right of the `gt` pointer are greater than the pivot value.
#   • Tips: Randomly shuffle the input or choose a random pivot to ensure average-case performance.; Employ 3-way partitioning to efficiently handle duplicate keys and avoid quadratic worst-case scenarios.
#   • Pitfalls: Failing to handle duplicate keys can lead to quadratic time complexity.; Incorrect pointer crossing logic can cause infinite loops or array out-of-bounds errors.
# - Scheduling jobs on two machines (array, number, simulation, enumeration)
#   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
#   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
#   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
#   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
#   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def sortColors(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        # 1. Dutch National Flag problem solution (three-way partitioning)
        # 2. Time complexity: O(N), Space complexity: O(1)

        lt, i, gt = 0, 0, len(nums) - 1

        while i <= gt:
            if nums[i] == 0:
                nums[lt], nums[i] = nums[i], nums[lt]
                lt += 1
                i += 1
            elif nums[i] == 1:
                i += 1
            else: # nums[i] == 2
                nums[gt], nums[i] = nums[i], nums[gt]
                gt -= 1