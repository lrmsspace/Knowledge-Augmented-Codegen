# Source: https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.
#
# An array A is a zigzag array if either:
#
#
#  Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
#  OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
#
#
# Return the minimum number of moves to transform the given array nums into a zigzag array.
#
# Example:
# Input: nums = [1,2,3]
# Output: 2
# Explanation: We can decrease 2 to 0 or 3 to 1.
#
# Constraints:
# 1 <= nums.length <= 1000
#  1 <= nums[i] <= 1000
#
# Helpful references (internal KB):
# - Scheduling jobs on two machines (array, greedy)
#   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
#   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
#   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
#   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
#   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
# - Manhattan Distance (array, number, enumeration, max-window)
#   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
#   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
#   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
#   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
#   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
# - Finding repetitions (string, array, z-function, enumeration)
#   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
#   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
#   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
#   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
#   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def movesToMakeZigzag(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def calculate_moves(nums, make_even_small):
            moves = 0
            n = len(nums)
            for i in range(n):
                left = nums[i - 1] if i - 1 >= 0 else float('inf')
                right = nums[i + 1] if i + 1 < n else float('inf')
                if (make_even_small and i % 2 == 0) or (not make_even_small and i % 2 == 1):
                    target_height = min(left, right) - 1
                    if nums[i] > target_height:
                        moves += nums[i] - target_height
            return moves

        moves_even_small = calculate_moves(nums, True)
        moves_odd_small = calculate_moves(nums, False)

        return min(moves_even_small, moves_odd_small)