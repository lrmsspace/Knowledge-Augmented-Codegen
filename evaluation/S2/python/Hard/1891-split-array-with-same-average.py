# Source: https://leetcode.com/problems/split-array-with-same-average/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums.
#
# You should move each element of nums into one of the two arrays A and B such that A and B are non-empty, and average(A) == average(B).
#
# Return true if it is possible to achieve that and false otherwise.
#
# Note that for an array arr, average(arr) is the sum of all the elements of arr over the length of arr.
#
# Example:
# Input: nums = [1,2,3,4,5,6,7,8]
# Output: true
# Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have an average of 4.5.
#
# Constraints:
# 1 <= nums.length <= 30
# 	0 <= nums[i] <= 104
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - bucket-sort (array, bucket-sort)
#   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
#   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
#   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
#   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
#   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
# - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
#   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
#   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
#   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
#   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
#   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def splitArraySameAverage(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        n, s = len(nums), sum(nums)
        for k in range(1, n//2+1):
            if s * k % n == 0 and self.dfs(nums, 0, k, s * k // n):
                return True
        return False