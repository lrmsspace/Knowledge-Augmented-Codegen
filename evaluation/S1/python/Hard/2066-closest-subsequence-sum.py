# Source: https://leetcode.com/problems/closest-subsequence-sum/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and an integer goal.
#
# You want to choose a subsequence of nums such that the sum of its elements is the closest possible to goal. That is, if the sum of the subsequence's elements is sum, then you want to minimize the absolute difference abs(sum - goal).
#
# Return the minimum possible value of abs(sum - goal).
#
# Note that a subsequence of an array is an array formed by removing some elements (possibly all or none) of the original array.
#
# Example:
# Input: nums = [5,-7,3,5], goal = 6
# Output: 0
# Explanation: Choose the whole array as a subsequence, with a sum of 6.
# This is equal to the goal, so the absolute difference is 0.
#
# Constraints:
# 1 <= nums.length <= 40
# 	-107 <= nums[i] <= 107
# 	-109 <= goal <= 109
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - Search for connected components in a graph (stack, graph, dfs, recursion)
#   • When to use: Use when the goal is to identify distinct groups of interconnected nodes within a graph, or to find all nodes reachable from a specific starting point.
#   • Idea: Depth-First Search (DFS) explores a graph by traversing as far as possible along each branch before backtracking. It efficiently finds connected components by visiting all reachable nodes from an unvisited starting point, typically with O(V+E) time complexity.
#   • Invariants: All nodes in the current DFS path from the start node to the current node are on the recursion stack.; Any node marked as visited will not be re-processed by the current DFS call.
#   • Tips: Maintain a 'visited' status for each node to prevent cycles and redundant work.; Iterate through all nodes and start DFS if a node is unvisited to find all components.
#   • Pitfalls: Excessive recursion depth can lead to stack overflow errors for large graphs.; Forgetting to mark nodes as visited results in infinite loops in cyclic graphs.
# - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
#   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
#   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
#   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
#   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
#   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minAbsDifference(self, nums, goal):
        """
        :type nums: List[int]
        :type goal: int
        :rtype: int
        """
        from bisect import bisect_left

        def get_subsequence_sums(arr):
            sums = {0}
            for num in arr:
                new_sums = set()
                for s in sums:
                    new_sums.add(s + num)
                sums |= new_sums
            return sorted(sums)

        n = len(nums)
        left_half = nums[:n//2]
        right_half = nums[n//2:]

        left_sums = get_subsequence_sums(left_half)
        right_sums = get_subsequence_sums(right_half)

        min_diff = float('inf')

        for s in left_sums:
            target = goal - s
            idx = bisect_left(right_sums, target)

            if idx < len(right_sums):
                min_diff = min(min_diff, abs(s + right_sums[idx] - goal))
            if idx > 0:
                min_diff = min(min_diff, abs(s + right_sums[idx - 1] - goal))

        return min_diff