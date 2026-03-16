# Source: https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array complexity of length n.
#
# There are n locked computers in a room with labels from 0 to n - 1, each with its own unique password. The password of the computer i has a complexity complexity[i].
#
# The password for the computer labeled 0 is already decrypted and serves as the root. All other computers must be unlocked using it or another previously unlocked computer, following this information:
#
#
#  You can decrypt the password for the computer i using the password for computer j, where j is any integer less than i with a lower complexity. (i.e. j < i and complexity[j] < complexity[i])
#  To decrypt the password for computer i, you must have already unlocked a computer j such that j < i and complexity[j] < complexity[i].
#
#
# Find the number of permutations of [0, 1, 2, ..., (n - 1)] that represent a valid order in which the computers can be unlocked, starting from computer 0 as the only initially unlocked one.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# Note that the password for the computer with label 0 is decrypted, and not the computer with the first position in the permutation.
#
# Example:
# Input: complexity = [1,2,3]
#
# Output: 2
#
# Explanation:
#
# The valid permutations are:
#
#
#  [0, 1, 2]
#  
#   Unlock computer 0 first with root password.
#   Unlock computer 1 with password of computer 0 since complexity[0] < complexity[1].
#   Unlock computer 2 with password of computer 1 since complexity[1] < complexity[2].
#  
#  
#  [0, 2, 1]
#  
#   Unlock computer 0 first with root password.
#   Unlock computer 2 with password of computer 0 since complexity[0] < complexity[2].
#   Unlock computer 1 with password of computer 0 since complexity[0] < complexity[1].
#
# Constraints:
# 2 <= complexity.length <= 105
#  1 <= complexity[i] <= 109
#
# Helpful references (internal KB):
# - Counting labeled graphs (number, dp-2d, counting, recursion)
#   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
#   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
#   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
#   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
#   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
# - Topological Sorting (graph, array, dfs, topo)
#   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
#   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
#   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
#   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
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
    def countPermutations(self, complexity):
        """
        :type complexity: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(complexity)
        
        # Precompute factorials and inverse factorials for combinations
        fact = [1] * (n + 1)
        for i in range(2, n + 1):
            fact[i] = fact[i - 1] * i % MOD
        
        inv_fact = [1] * (n + 1)
        inv_fact[n] = pow(fact[n], MOD - 2, MOD)
        for i in range(n - 1, 0, -1):
            inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD
        
        def comb(a, b):
            if b > a or b < 0:
                return 0
            return fact[a] * inv_fact[b] % MOD * inv_fact[a - b] % MOD
        
        from functools import lru_cache
        
        @lru_cache(None)
        def dfs(start, end):
            if end - start <= 1:
                return 1
            
            root_complexity = complexity[start]
            left_indices = [i for i in range(start + 1, end) if complexity[i] < root_complexity]
            right_indices = [i for i in range(start + 1, end) if complexity[i] >= root_complexity]
            
            left_count = len(left_indices)
            right_count = len(right_indices)
            
            left_ways = dfs(start + 1, start + 1 + left_count)
            right_ways = dfs(start + 1 + left_count, end)
            
            total_ways = comb(left_count + right_count, left_count) * left_ways % MOD * right_ways % MOD
            return total_ways % MOD
        
        return dfs(0, n) % MOD