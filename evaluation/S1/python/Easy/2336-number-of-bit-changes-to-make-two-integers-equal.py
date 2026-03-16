# Source: https://leetcode.com/problems/number-of-bit-changes-to-make-two-integers-equal/   |   Difficulty: Easy
#
# Problem Description:
# You are given two positive integers n and k.
#
# You can choose any bit in the binary representation of n that is equal to 1 and change it to 0.
#
# Return the number of changes needed to make n equal to k. If it is impossible, return -1.
#
# Example:
# Input: n = 13, k = 4
#
# Output: 2
#
# Explanation:
# Initially, the binary representations of n and k are n = (1101)2 and k = (0100)2.
# We can change the first and fourth bits of n. The resulting integer is n = (0100)2 = k.
#
# Constraints:
# 1 <= n, k <= 106
#
# Helpful references (internal KB):
# - Bit manipulation (number, simulation)
#   • When to use: Use when operations on individual bits of an integer are required, for optimizing arithmetic with powers of two, or for efficient management of boolean flags.
#   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators and shifts. These operations typically have O(1) time complexity as they are hardware-level instructions.
#   • Invariants: The total number of bits representing the integer remains constant for fixed-width types.; Applying `n & (1 << k)` isolates the k-th bit, setting all other bits to zero.
#   • Tips: Use `&` with `(1 << k)` to check if the k-th bit is set.; Use `|` with `(1 << k)` to set the k-th bit.
#   • Pitfalls: Be aware of integer overflow when performing large left shifts.; Understand the difference between arithmetic and logical right shifts, especially for signed numbers.
# - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
#   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
#   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
#   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
#   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
#   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
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
    def minChanges(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        if k > n:
            return -1
        
        changes = 0
        while n > 0 or k > 0:
            n_bit = n & 1
            k_bit = k & 1
            
            if k_bit == 1 and n_bit == 0:
                return -1
            elif k_bit == 0 and n_bit == 1:
                changes += 1
            
            n >>= 1
            k >>= 1
        
        return changes