# Source: https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers n and m that consist of the same number of digits.
#
# You can perform the following operations any number of times:
#
#
# 	Choose any digit from n that is not 9 and increase it by 1.
# 	Choose any digit from n that is not 0 and decrease it by 1.
#
#
# The integer n must not be a prime number at any point, including its original value and after each operation.
#
# The cost of a transformation is the sum of all values that n takes throughout the operations performed.
#
# Return the minimum cost to transform n into m. If it is impossible, return -1.
#
# Example:
# Input: n = 10, m = 12
#
# Output: 85
#
# Explanation:
#
# We perform the following operations:
#
#
# 	Increase the first digit, now n = 20.
# 	Increase the second digit, now n = 21.
# 	Increase the second digit, now n = 22.
# 	Decrease the first digit, now n = 12.
#
# Constraints:
# 1 <= n, m < 104
# 	n and m consist of the same number of digits.
#
# Helpful references (internal KB):
# - Sieve of Eratosthenes (array, bitset, sieve)
#   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
#   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
#   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
#   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
# - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
#   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
#   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
#   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
#   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
#   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minOperations(self, n, m):
        """
        :type n: int
        :type m: int
        :rtype: int
        """
        MAX_N = 10000

        # Sieve of Eratosthenes to find all primes up to MAX_N
        is_prime = [True] * MAX_N
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(MAX_N**0.5) + 1):
            if is_prime[i]:
                for j in range(i * i, MAX_N, i):
                    is_prime[j] = False

        from collections import deque, defaultdict

        def get_neighbors(num):
            neighbors = []
            num_str = str(num)
            for i in range(len(num_str)):
                digit = int(num_str[i])
                for change in [-1, 1]:
                    new_digit = digit + change
                    if 0 <= new_digit <= 9:
                        new_num_str = num_str[:i] + str(new_digit) + num_str[i+1:]
                        new_num = int(new_num_str)
                        if not is_prime[new_num]:
                            neighbors.append(new_num)
            return neighbors

        # BFS to find the minimum cost path from n to m
        queue = deque([(n, n)])  # (current number, cumulative cost)
        visited = defaultdict(lambda: float('inf'))
        visited[n] = n

        while queue:
            current, cost = queue.popleft()
            if current == m:
                return cost

            for neighbor in get_neighbors(current):
                new_cost = cost + neighbor
                if new_cost < visited[neighbor]:
                    visited[neighbor] = new_cost
                    queue.append((neighbor, new_cost))

        return -1