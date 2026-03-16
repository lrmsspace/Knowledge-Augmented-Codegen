# Source: https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/   |   Difficulty: Hard
#
# Problem Description:
# You want to build some obstacle courses. You are given a 0-indexed integer array obstacles of length n, where obstacles[i] describes the height of the ith obstacle.
#
# For every index i between 0 and n - 1 (inclusive), find the length of the longest obstacle course in obstacles such that:
#
#
# 	You choose any number of obstacles between 0 and i inclusive.
# 	You must include the ith obstacle in the course.
# 	You must put the chosen obstacles in the same order as they appear in obstacles.
# 	Every obstacle (except the first) is taller than or the same height as the obstacle immediately before it.
#
#
# Return an array ans of length n, where ans[i] is the length of the longest obstacle course for index i as described above.
#
# Example:
# Input: obstacles = [1,2,3,2]
# Output: [1,2,3,3]
# Explanation: The longest valid obstacle course at each position is:
# - i = 0: [1], [1] has length 1.
# - i = 1: [1,2], [1,2] has length 2.
# - i = 2: [1,2,3], [1,2,3] has length 3.
# - i = 3: [1,2,3,2], [1,2,2] has length 3.
#
# Constraints:
# n == obstacles.length
# 	1 <= n <= 105
# 	1 <= obstacles[i] <= 107
#
# Helpful references (internal KB):
# - Longest increasing subsequence (array, dp-1d, binary-search)
#   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
#   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
#   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
#   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
#   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
# - Binary search (interval, number, binary-search-answer, enumeration)
#   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
#   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
#   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
#   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
#   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
# - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
#   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
#   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
#   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
#   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
#   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def longestObstacleCourseAtEachPosition(self, obstacles):
        """
        :type obstacles: List[int]
        :rtype: List[int]
        """
        from bisect import bisect_right
        
        n = len(obstacles)
        ans = [0] * n
        tails = []
        
        for i in range(n):
            height = obstacles[i]
            # Find the position to insert height in tails
            pos = bisect_right(tails, height)
            
            # If pos is equal to the length of tails, it means height is greater than all elements in tails
            if pos == len(tails):
                tails.append(height)
            else:
                tails[pos] = height
            
            ans[i] = pos + 1  # Length is position + 1 (1-based index)
        
        return ans