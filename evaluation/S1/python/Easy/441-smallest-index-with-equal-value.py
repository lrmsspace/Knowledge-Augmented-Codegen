# Source: https://leetcode.com/problems/smallest-index-with-equal-value/   |   Difficulty: Easy
#
# Problem Description:
# Given a 0-indexed integer array nums, return the smallest index i of nums such that i mod 10 == nums[i], or -1 if such index does not exist.
#
# x mod y denotes the remainder when x is divided by y.
#
# Example:
# Input: nums = [0,1,2]
# Output: 0
# Explanation: 
# i=0: 0 mod 10 = 0 == nums[0].
# i=1: 1 mod 10 = 1 == nums[1].
# i=2: 2 mod 10 = 2 == nums[2].
# All indices have i mod 10 == nums[i], so we return the smallest index 0.
#
# Constraints:
# 1 <= nums.length <= 100
# 	0 <= nums[i] <= 9
#
# Helpful references (internal KB):
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - Primality tests (number, enumeration, simulation)
#   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
#   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
#   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
#   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
#   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
# - Simulated Annealing (array, number, randomized, simulation)
#   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
#   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
#   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
#   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
#   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def smallestEqual(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        for i in range(len(nums)):
            if i % 10 == nums[i]:
                return i
        return -1