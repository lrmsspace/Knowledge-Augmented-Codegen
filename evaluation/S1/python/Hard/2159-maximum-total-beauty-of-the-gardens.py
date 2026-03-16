# Source: https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/   |   Difficulty: Hard
#
# Problem Description:
# Alice is a caretaker of n gardens and she wants to plant flowers to maximize the total beauty of all her gardens.
#
# You are given a 0-indexed integer array flowers of size n, where flowers[i] is the number of flowers already planted in the ith garden. Flowers that are already planted cannot be removed. You are then given another integer newFlowers, which is the maximum number of flowers that Alice can additionally plant. You are also given the integers target, full, and partial.
#
# A garden is considered complete if it has at least target flowers. The total beauty of the gardens is then determined as the sum of the following:
#
#
# 	The number of complete gardens multiplied by full.
# 	The minimum number of flowers in any of the incomplete gardens multiplied by partial. If there are no incomplete gardens, then this value will be 0.
#
#
# Return the maximum total beauty that Alice can obtain after planting at most newFlowers flowers.
#
# Example:
# Input: flowers = [1,3,1,1], newFlowers = 7, target = 6, full = 12, partial = 1
# Output: 14
# Explanation: Alice can plant
# - 2 flowers in the 0th garden
# - 3 flowers in the 1st garden
# - 1 flower in the 2nd garden
# - 1 flower in the 3rd garden
# The gardens will then be [3,6,2,2]. She planted a total of 2 + 3 + 1 + 1 = 7 flowers.
# There is 1 garden that is complete.
# The minimum number of flowers in the incomplete gardens is 2.
# Thus, the total beauty is 1 * 12 + 2 * 1 = 12 + 2 = 14.
# No other way of planting flowers can obtain a total beauty higher than 14.
#
# Constraints:
# 1 <= flowers.length <= 105
# 	1 <= flowers[i], target <= 105
# 	1 <= newFlowers <= 1010
# 	1 <= full, partial <= 105
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
#   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
#   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
#   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
#   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
#   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
# - Mergesort (array, merge-sort, divide-and-conquer, recursion)
#   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
#   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
#   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
#   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
#   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumBeauty(self, flowers, newFlowers, target, full, partial):
        """
        :type flowers: List[int]
        :type newFlowers: int
        :type target: int
        :type full: int
        :type partial: int
        :rtype: int
        """
        # Step 1: Count the number of complete gardens and calculate the total beauty from them.
        complete_gardens = sum(1 for f in flowers if f >= target)
        total_beauty = complete_gardens * full

        # Step 2: Calculate the number of flowers needed to complete each incomplete garden.
        incomplete_gardens = [f for f in flowers if f < target]
        needed_flowers = [target - f for f in incomplete_gardens]

        # Step 3: Sort the needed flowers in ascending order to prioritize completing gardens with fewer flowers needed.
        needed_flowers.sort()

        # Step 4: Use a greedy approach to plant flowers in incomplete gardens until we run out of newFlowers.
        for needed in needed_flowers:
            if newFlowers >= needed:
                newFlowers -= needed
                total_beauty += full  # This garden is now complete
            else:
                # If we can't complete this garden, we can only plant some flowers to increase its beauty.
                total_beauty += (newFlowers * partial) // needed  # Partial beauty contribution
                break

        return total_beauty