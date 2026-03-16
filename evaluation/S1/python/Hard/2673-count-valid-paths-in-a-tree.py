# Source: https://leetcode.com/problems/count-valid-paths-in-a-tree/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 1 to n. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
#
# Return the number of valid paths in the tree.
#
# A path (a, b) is valid if there exists exactly one prime number among the node labels in the path from a to b.
#
# Note that:
#
#
# 	The path (a, b) is a sequence of distinct nodes starting with node a and ending with node b such that every two adjacent nodes in the sequence share an edge in the tree.
# 	Path (a, b) and path (b, a) are considered the same and counted only once.
#
# Example:
# Input: n = 5, edges = [[1,2],[1,3],[2,4],[2,5]]
# Output: 4
# Explanation: The pairs with exactly one prime number on the path between them are: 
# - (1, 2) since the path from 1 to 2 contains prime number 2. 
# - (1, 3) since the path from 1 to 3 contains prime number 3.
# - (1, 4) since the path from 1 to 4 contains prime number 2.
# - (2, 4) since the path from 2 to 4 contains prime number 2.
# It can be shown that there are only 4 valid paths.
#
# Constraints:
# 1 <= n <= 105
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	1 <= ui, vi <= n
# 	The input is generated such that edges represent a valid tree.
#
# Helpful references (internal KB):
# - Sieve of Eratosthenes (array, bitset, sieve)
#   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
#   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
#   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
#   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
# - Undirected Graphs (graph, array, simulation)
#   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
#   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
#   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
#   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
#   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
# - Counting labeled graphs (number, recursion, counting, dp-1d)
#   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
#   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
#   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
#   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
#   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countPaths(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        # Step 1: Identify prime numbers up to n using Sieve of Eratosthenes
        is_prime = [True] * (n + 1)
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(n**0.5) + 1):
            if is_prime[i]:
                for j in range(i * i, n + 1, i):
                    is_prime[j] = False

        # Step 2: Build the graph as an adjacency list
        graph = [[] for _ in range(n + 1)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        # Step 3: Count valid paths using DFS
        def dfs(node, parent):
            count = 0
            prime_count = 1 if is_prime[node] else 0
            
            for neighbor in graph[node]:
                if neighbor == parent:
                    continue
                sub_count, sub_prime_count = dfs(neighbor, node)
                count += sub_count
                prime_count += sub_prime_count
            
            # If the current path has exactly one prime number, count it as valid
            if prime_count == 1:
                count += 1
            
            return count, prime_count

        total_paths, _ = dfs(1, -1)  # Start DFS from node 1
        return total_paths // 2  # Each path is counted twice (a,b) and (b,a)