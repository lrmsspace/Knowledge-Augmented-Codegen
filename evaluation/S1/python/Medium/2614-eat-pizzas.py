# Source: https://leetcode.com/problems/eat-pizzas/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array pizzas of size n, where pizzas[i] represents the weight of the ith pizza. Every day, you eat exactly 4 pizzas. Due to your incredible metabolism, when you eat pizzas of weights W, X, Y, and Z, where W <= X <= Y <= Z, you gain the weight of only 1 pizza!
#
#
# 	On odd-numbered days (1-indexed), you gain a weight of Z.
# 	On even-numbered days, you gain a weight of Y.
#
#
# Find the maximum total weight you can gain by eating all pizzas optimally.
#
# Note: It is guaranteed that n is a multiple of 4, and each pizza can be eaten only once.
#
# Example:
# Input: pizzas = [1,2,3,4,5,6,7,8]
#
# Output: 14
#
# Explanation:
#
#
# 	On day 1, you eat pizzas at indices [1, 2, 4, 7] = [2, 3, 5, 8]. You gain a weight of 8.
# 	On day 2, you eat pizzas at indices [0, 3, 5, 6] = [1, 4, 6, 7]. You gain a weight of 6.
#
#
# The total weight gained after eating all the pizzas is 8 + 6 = 14.
#
# Constraints:
# 4 <= n == pizzas.length <= 2 * 105
# 	1 <= pizzas[i] <= 105
# 	n is a multiple of 4.
#
# Helpful references (internal KB):
# - kth-largest-element-in-an-array (array, merge-sort)
#   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
#   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
#   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
#   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
#   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
# - Knapsack Problem (array, knapsack, dp-1d, enumeration)
#   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
#   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
#   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
#   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
#   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
# - Scheduling jobs on two machines (array, greedy)
#   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
#   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
#   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
#   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
#   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxWeight(self, pizzas):
        """
        :type pizzas: List[int]
        :rtype: int
        """
        pizzas.sort()
        n = len(pizzas)
        total_weight = 0
        
        # Eat pizzas in groups of 4
        for i in range(n // 4):
            # On odd days, gain weight of the heaviest pizza (4th pizza in sorted order)
            total_weight += pizzas[n - 1 - i * 2]
            # On even days, gain weight of the second heaviest pizza (3rd pizza in sorted order)
            total_weight += pizzas[n - 2 - i * 2]
        
        return total_weight