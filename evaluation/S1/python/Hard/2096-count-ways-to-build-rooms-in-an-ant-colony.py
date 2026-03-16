# Source: https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/   |   Difficulty: Hard
#
# Problem Description:
# You are an ant tasked with adding n new rooms numbered 0 to n-1 to your colony. You are given the expansion plan as a 0-indexed integer array of length n, prevRoom, where prevRoom[i] indicates that you must build room prevRoom[i] before building room i, and these two rooms must be connected directly. Room 0 is already built, so prevRoom[0] = -1. The expansion plan is given such that once all the rooms are built, every room will be reachable from room 0.
#
# You can only build one room at a time, and you can travel freely between rooms you have already built only if they are connected. You can choose to build any room as long as its previous room is already built.
#
# Return the number of different orders you can build all the rooms in. Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: prevRoom = [-1,0,1]
# Output: 1
# Explanation: There is only one way to build the additional rooms: 0 → 1 → 2
#
# Constraints:
# n == prevRoom.length
# 	2 <= n <= 105
# 	prevRoom[0] == -1
# 	0 <= prevRoom[i] < n for all 1 <= i < n
# 	Every room is reachable from room 0 once all the rooms are built.
#
# Helpful references (internal KB):
# - Binomial Coefficients (array, number, mod-exp, enumeration)
#   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
#   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
#   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
#   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
#   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):

    def waysToBuildRooms(self, prevRoom):

        """

        :type prevRoom: List[int]

        :rtype: int

        """
        from collections import defaultdict
        import math

        mod = 10**9 + 7
        n = len(prevRoom)

        # Build the adjacency list for the tree structure of rooms
        tree = defaultdict(list)
        for i in range(1, n):
            tree[prevRoom[i]].append(i)

        # Precompute factorials and modular inverses for binomial coefficients
        MAXN = n + 1
        fact = [1] * MAXN
        invFact = [1] * MAXN

        for i in range(2, MAXN):
            fact[i] = fact[i-1] * i % mod

        invFact[MAXN - 1] = pow(fact[MAXN - 1], mod - 2, mod)
        for i in range(MAXN - 2, -1, -1):
            invFact[i] = invFact[i + 1] * (i + 1) % mod

        def binomial(n, k):
            if k > n or k < 0:
                return 0
            return fact[n] * invFact[k] % mod * invFact[n - k] % mod

        def dfs(node):
            total_ways = 1
            total_size = 0

            for child in tree[node]:
                child_ways, child_size = dfs(child)
                total_ways = total_ways * child_ways % mod
                total_ways = total_ways * binomial(total_size + child_size, child_size) % mod
                total_size += child_size

            return total_ways, total_size + 1

        result, _ = dfs(0)
        return result