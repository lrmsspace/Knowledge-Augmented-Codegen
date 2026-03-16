# Source: https://leetcode.com/problems/minimum-number-of-coins-to-be-added/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array coins, representing the values of the coins available, and an integer target.
#
# An integer x is obtainable if there exists a subsequence of coins that sums to x.
#
# Return the minimum number of coins of any value that need to be added to the array so that every integer in the range [1, target] is obtainable.
#
# A subsequence of an array is a new non-empty array that is formed from the original array by deleting some (possibly none) of the elements without disturbing the relative positions of the remaining elements.
#
# Example:
# Input: coins = [1,4,10], target = 19
# Output: 2
# Explanation: We need to add coins 2 and 8. The resulting array will be [1,2,4,8,10].
# It can be shown that all integers from 1 to 19 are obtainable from the resulting array, and that 2 is the minimum number of coins that need to be added to the array.
#
# Constraints:
# 1 <= target <= 105
# 	1 <= coins.length <= 105
# 	1 <= coins[i] <= target
#
# Helpful references (internal KB):
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
    def minimumAddedCoins(self, coins, target):
        """
        :type coins: List[int]
        :type target: int
        :rtype: int
        """
        coins.sort()
        added_coins = 0
        current_sum = 0

        for coin in coins:
            while current_sum + 1 < coin and current_sum < target:
                added_coins += 1
                current_sum += current_sum + 1
            if current_sum >= target:
                break
            current_sum += coin

        while current_sum < target:
            added_coins += 1
            current_sum += current_sum + 1

        return added_coins