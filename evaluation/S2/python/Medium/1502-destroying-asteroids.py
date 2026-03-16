# Source: https://leetcode.com/problems/destroying-asteroids/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer mass, which represents the original mass of a planet. You are further given an integer array asteroids, where asteroids[i] is the mass of the ith asteroid.
#
# You can arrange for the planet to collide with the asteroids in any arbitrary order. If the mass of the planet is greater than or equal to the mass of the asteroid, the asteroid is destroyed and the planet gains the mass of the asteroid. Otherwise, the planet is destroyed.
#
# Return true if all asteroids can be destroyed. Otherwise, return false.
#
# Example:
# Input: mass = 10, asteroids = [3,9,19,5,21]
# Output: true
# Explanation: One way to order the asteroids is [9,19,5,3,21]:
# - The planet collides with the asteroid with a mass of 9. New planet mass: 10 + 9 = 19
# - The planet collides with the asteroid with a mass of 19. New planet mass: 19 + 19 = 38
# - The planet collides with the asteroid with a mass of 5. New planet mass: 38 + 5 = 43
# - The planet collides with the asteroid with a mass of 3. New planet mass: 43 + 3 = 46
# - The planet collides with the asteroid with a mass of 21. New planet mass: 46 + 21 = 67
# All asteroids are destroyed.
#
# Constraints:
# 1 <= mass <= 105
# 	1 <= asteroids.length <= 105
# 	1 <= asteroids[i] <= 105
#
# Helpful references (internal KB):
# - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
#   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
#   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
#   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
#   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
#   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
# - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
#   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
#   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
#   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
#   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
#   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
# - kth-largest-element-in-an-array (array, merge-sort)
#   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
#   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
#   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
#   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
#   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def asteroidsDestroyed(self, mass, asteroids):
        """
        :type mass: int
        :type asteroids: List[int]
        :rtype: bool
        """
        # Sort the asteroids in ascending order to ensure we always try to destroy the smallest asteroid first.
        asteroids.sort()

        for asteroid in asteroids:
            if mass < asteroid:
                return False  # If the current mass is less than the asteroid, we cannot destroy it.
            mass += asteroid
        return True  # If we have successfully destroyed all asteroids, return True.