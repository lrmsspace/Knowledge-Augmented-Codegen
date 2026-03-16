# Source: https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D array queries, where queries[i] is of the form [l, r]. Each queries[i] defines an array of integers nums consisting of elements ranging from l to r, both inclusive.
#
# In one operation, you can:
#
#
# 	Select two integers a and b from the array.
# 	Replace them with floor(a / 4) and floor(b / 4).
#
#
# Your task is to determine the minimum number of operations required to reduce all elements of the array to zero for each query. Return the sum of the results for all queries.
#
# Example:
# Input: queries = [[1,2],[2,4]]
#
# Output: 3
#
# Explanation:
#
# For queries[0]:
#
#
# 	The initial array is nums = [1, 2].
# 	In the first operation, select nums[0] and nums[1]. The array becomes [0, 0].
# 	The minimum number of operations required is 1.
#
#
# For queries[1]:
#
#
# 	The initial array is nums = [2, 3, 4].
# 	In the first operation, select nums[0] and nums[2]. The array becomes [0, 3, 1].
# 	In the second operation, select nums[1] and nums[2]. The array becomes [0, 0, 0].
# 	The minimum number of operations required is 2.
#
#
# The output is 1 + 2 = 3.
#
# Constraints:
# 1 <= queries.length <= 105
# 	queries[i].length == 2
# 	queries[i] == [l, r]
# 	1 <= l < r <= 109
#
# Helpful references (internal KB):
# - Range Minimum Query (array, ds, divide-and-conquer)
#   • When to use: Use when you need to find the minimum element within specified ranges of an array efficiently, especially for many queries after initial setup.
#   • Idea: A Range Minimum Query (RMQ) problem asks to find the minimum value in a specified range [L, R] of an array. It can be solved with various data structures, often achieving O(1) or O(log N) query time after O(N log N) or O(N) precomputation.
#   • Invariants: For any query range [L, R], the returned value is the minimum of elements A[i] where L <= i <= R.; The precomputed data structure correctly stores minimums for all relevant sub-intervals.
#   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) precomputation.; For dynamic arrays (with updates), Segment Tree provides O(log N) query and update times.
#   • Pitfalls: Incorrectly handling edge cases for range boundaries (L, R).; High memory usage for Sparse Table if N is very large (N log N space).
# - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
#   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
#   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
#   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
#   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
#   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
#   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
#   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
#   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
#   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOperations(self, queries):
        """
        :type queries: List[List[int]]
        :rtype: int
        """
        def count_operations(n):
            if n <= 1:
                return 0
            operations = 0
            while n > 1:
                n //= 4
                operations += 1
            return operations

        total_operations = 0
        for l, r in queries:
            for num in range(l, r + 1):
                total_operations += count_operations(num)

        return total_operations