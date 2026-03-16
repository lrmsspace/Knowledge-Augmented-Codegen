# Source: https://leetcode.com/problems/distribute-candies-among-children-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given two positive integers n and limit.
#
# Return the total number of ways to distribute n candies among 3 children such that no child gets more than limit candies.
#
# Example:
# Input: n = 5, limit = 2
# Output: 3
# Explanation: There are 3 ways to distribute 5 candies such that no child gets more than 2 candies: (1, 2, 2), (2, 1, 2) and (2, 2, 1).
#
# Constraints:
# 1 <= n <= 50
# 	1 <= limit <= 50
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Catalan Numbers (number, counting)
#   • When to use: Use when counting arrangements of objects that follow a specific non-crossing or balancing rule, often involving recursive decomposition or paths constrained by a diagonal.
#   • Idea: Catalan numbers count the number of ways to arrange certain combinatorial objects, such as balanced parentheses sequences or monotonic paths that do not cross a diagonal. They can be computed using a recurrence relation (O(N^2) with DP) or a direct binomial coefficient formula (O(N) or O(N log N)).
#   • Invariants: dp[i] stores the i-th Catalan number, correctly computed from dp[0] through dp[i-1].; For each n, the sum sum(dp[k] * dp[n-1-k]) iterates through all valid partitions of the problem.
#   • Tips: Memoize the recursive solution to avoid redundant computations, transforming it into dynamic programming.; For large N, use modular arithmetic if results are required modulo a prime to prevent integer overflow.
#   • Pitfalls: Forgetting to correctly handle the base cases, typically C0 = 1 and C1 = 1.; Encountering integer overflow when calculating large binomial coefficients without appropriate modular arithmetic.
# - Stars and bars (number, counting)
#   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative integer solutions to a linear equation. It is also applicable for problems with lower bounds on variables.
#   • Idea: Stars and bars is a combinatorial technique used to count the number of ways to place 'n' identical items into 'k' distinct bins, or equivalently, to find the number of non-negative integer solutions to x1 + ... + xk = n.
#   • Invariants: The total number of 'stars' (items) remains constant throughout any transformation.; The number of 'bars' (separators) is always one less than the number of bins (variables).
#   • Tips: Visualize items as 'stars' and separators as 'bars' to understand the arrangement.; Transform problems with lower bounds (x_i >= a_i) into non-negative solutions (x_i' >= 0).
#   • Pitfalls: Confusing identical items with distinct items, which requires a different counting method.; Incorrectly applying the formula when variables have lower bounds other than zero without transformation.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def distributeCandies(self, n, limit):
        """
        :type n: int
        :type limit: int
        :rtype: int
        """
        count = 0
        for i in range(min(limit, n) + 1):
            for j in range(min(limit, n - i) + 1):
                k = n - i - j
                if 0 <= k <= limit:
                    count += 1
        return count