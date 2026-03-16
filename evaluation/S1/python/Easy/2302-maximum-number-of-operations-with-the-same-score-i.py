# Source: https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of integers nums. Consider the following operation:
#
#
# 	Delete the first two elements nums and define the score of the operation as the sum of these two elements.
#
#
# You can perform this operation until nums contains fewer than two elements. Additionally, the same score must be achieved in all operations.
#
# Return the maximum number of operations you can perform.
#
# Example:
# Input: nums = [3,2,1,4,5]
#
# Output: 2
#
# Explanation:
#
#
# 	We can perform the first operation with the score 3 + 2 = 5. After this operation, nums = [1,4,5].
# 	We can perform the second operation as its score is 4 + 1 = 5, the same as the previous operation. After this operation, nums = [5].
# 	As there are fewer than two elements, we can't perform more operations.
#
# Constraints:
# 2 <= nums.length <= 100
# 	1 <= nums[i] <= 1000
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Scheduling jobs on two machines (array, number, simulation, enumeration)
#   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
#   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
#   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
#   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
#   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
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
    def maxOperations(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import Counter

        count = Counter(nums)
        operations = 0

        for num in list(count.keys()):
            complement = max(nums) + 1 - num
            if complement in count:
                if num == complement:
                    operations += count[num] // 2
                else:
                    pairs = min(count[num], count[complement])
                    operations += pairs
                    count[complement] -= pairs
            count[num] = 0

        return operations