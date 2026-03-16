# Source: https://leetcode.com/problems/soup-servings/   |   Difficulty: Medium
#
# Problem Description:
# You have two soups, A and B, each starting with n mL. On every turn, one of the following four serving operations is chosen at random, each with probability 0.25 independent of all previous turns:
#
#
# 	pour 100 mL from type A and 0 mL from type B
# 	pour 75 mL from type A and 25 mL from type B
# 	pour 50 mL from type A and 50 mL from type B
# 	pour 25 mL from type A and 75 mL from type B
#
#
# Note:
#
#
# 	There is no operation that pours 0 mL from A and 100 mL from B.
# 	The amounts from A and B are poured simultaneously during the turn.
# 	If an operation asks you to pour more than you have left of a soup, pour all that remains of that soup.
#
#
# The process stops immediately after any turn in which one of the soups is used up.
#
# Return the probability that A is used up before B, plus half the probability that both soups are used up in the same turn. Answers within 10-5 of the actual answer will be accepted.
#
# Example:
# Input: n = 50
# Output: 0.62500
# Explanation: 
# If we perform either of the first two serving operations, soup A will become empty first.
# If we perform the third operation, A and B will become empty at the same time.
# If we perform the fourth operation, B will become empty first.
# So the total probability of A becoming empty first plus half the probability that A and B become empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.
#
# Constraints:
# 0 <= n <= 109
#
# Helpful references (internal KB):
# - Reservoir Sampling (array, randomized, simulation)
#   • When to use: When you need to randomly select a fixed number of items (k) from a stream or a very large dataset of unknown size, ensuring each item has an equal probability of selection in a single pass.
#   • Idea: Reservoir sampling is a randomized algorithm that selects k items from a list containing n items, where n is either a very large or unknown number, ensuring each item has an equal probability of being selected. It processes the input in a single pass with O(N) time complexity and O(k) space complexity.
#   • Invariants: The reservoir always contains exactly k elements.; Any element processed up to the current index `i` has a k/(i+1) probability of being in the reservoir.
#   • Tips: Initialize the reservoir with the first k elements from the stream.; For each subsequent element, generate a random index from 0 to current_stream_index.
#   • Pitfalls: Failing to correctly initialize the reservoir with the first k elements.; Generating random indices outside the valid range [0, current_stream_index] or [0, k-1].
# - Simulated Annealing (array, number, randomized, simulation)
#   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
#   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
#   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
#   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
#   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
# - Maximum flow - Push-relabel algorithm (graph, number, simulation)
#   • When to use: Use when finding the maximum flow in a network, particularly for dense graphs or when the Ford-Fulkerson method is too slow due to many augmenting paths.
#   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from higher to lower nodes and relabeling nodes until all excess is pushed to the sink. It is a highly efficient polynomial-time algorithm for various graph structures.
#   • Invariants: For any vertex v (not source or sink), the total incoming flow minus total outgoing flow is non-negative (excess flow).; For any edge (u, v) in the residual graph with positive capacity, the height of u is at most h(v) + 1.
#   • Tips: Understand the concepts of preflow and excess flow.; Correctly implement push and relabel operations.
#   • Pitfalls: Incorrectly updating residual capacities after a push.; Failing to maintain the height function property (h(u) <= h(v) + 1).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def soupServings(self, n):
        """
        :type n: int
        :rtype: float
        """
        if n >= 4800:
            return 1.0
        
        memo = {}
        
        def dfs(a, b):
            if (a, b) in memo:
                return memo[(a, b)]
            
            if a <= 0 and b <= 0:
                return 0.5
            if a <= 0:
                return 1.0
            if b <= 0:
                return 0.0
            
            memo[(a, b)] = 0.25 * (dfs(a - 100, b) + dfs(a - 75, b - 25) + dfs(a - 50, b - 50) + dfs(a - 25, b - 75))
            return memo[(a, b)]
        
        return dfs(n, n)