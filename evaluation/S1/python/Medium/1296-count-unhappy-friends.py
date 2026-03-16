# Source: https://leetcode.com/problems/count-unhappy-friends/   |   Difficulty: Medium
#
# Problem Description:
# You are given a list of preferences for n friends, where n is always even.
#
# For each person i, preferences[i] contains a list of friends sorted in the order of preference. In other words, a friend earlier in the list is more preferred than a friend later in the list. Friends in each list are denoted by integers from 0 to n-1.
#
# All the friends are divided into pairs. The pairings are given in a list pairs, where pairs[i] = [xi, yi] denotes xi is paired with yi and yi is paired with xi.
#
# However, this pairing may cause some of the friends to be unhappy. A friend x is unhappy if x is paired with y and there exists a friend u who is paired with v but:
#
#
# 	x prefers u over y, and
# 	u prefers x over v.
#
#
# Return the number of unhappy friends.
#
# Example:
# Input: n = 4, preferences = [[1, 2, 3], [3, 2, 0], [3, 1, 0], [1, 2, 0]], pairs = [[0, 1], [2, 3]]
# Output: 2
# Explanation:
# Friend 1 is unhappy because:
# - 1 is paired with 0 but prefers 3 over 0, and
# - 3 prefers 1 over 2.
# Friend 3 is unhappy because:
# - 3 is paired with 2 but prefers 1 over 2, and
# - 1 prefers 3 over 0.
# Friends 0 and 2 are happy.
#
# Constraints:
# 2 <= n <= 500
# 	n is even.
# 	preferences.length == n
# 	preferences[i].length == n - 1
# 	0 <= preferences[i][j] <= n - 1
# 	preferences[i] does not contain i.
# 	All values in preferences[i] are unique.
# 	pairs.length == n/2
# 	pairs[i].length == 2
# 	xi != yi
# 	0 <= xi, yi <= n - 1
# 	Each person is contained in exactly one pair.
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
#   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
#   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
#   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
#   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
#   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def unhappyFriends(self, n, preferences, pairs):
        """
        :type n: int
        :type preferences: List[List[int]]
        :type pairs: List[List[int]]
        :rtype: int
        """
        # Build a preference rank matrix for quick lookup
        rank = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n - 1):
                rank[i][preferences[i][j]] = j

        # Create a pair mapping for easy access
        pair_map = {}
        for x, y in pairs:
            pair_map[x] = y
            pair_map[y] = x

        unhappy_count = 0

        # Check each friend to see if they are unhappy
        for x in range(n):
            y = pair_map[x]
            y_rank = rank[x][y]
            for u in preferences[x][:y_rank]:
                v = pair_map[u]
                if rank[u][x] < rank[u][v]:
                    unhappy_count += 1
                    break

        return unhappy_count