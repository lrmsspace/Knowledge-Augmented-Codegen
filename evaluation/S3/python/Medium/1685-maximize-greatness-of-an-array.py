# Source: https://leetcode.com/problems/maximize-greatness-of-an-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums. You are allowed to permute nums into a new array perm of your choosing.
#
# We define the greatness of nums be the number of indices 0 <= i < nums.length for which perm[i] > nums[i].
#
# Return the maximum possible greatness you can achieve after permuting nums.
#
# Example:
# Input: nums = [1,3,5,2,1,3,1]
# Output: 4
# Explanation: One of the optimal rearrangements is perm = [2,5,1,3,3,1,1].
# At indices = 0, 1, 3, and 4, perm[i] > nums[i]. Hence, we return 4.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 109
#
# Helpful references (internal KB):
# - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
#   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
#   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
#   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
#   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
#   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
#   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
#   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
#   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
#   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
#   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
#   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
#   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
#   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximizeGreatness(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        greatness = 0
        j = 0

        for i in range(len(nums)):
            while j < len(nums) and nums[j] <= nums[i]:
                j += 1
            if j < len(nums):
                greatness += 1
                j += 1

        return greatness