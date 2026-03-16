# Source: https://leetcode.com/problems/create-components-with-same-value/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 0 to n - 1.
#
# You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# You are allowed to delete some edges, splitting the tree into multiple connected components. Let the value of a component be the sum of all nums[i] for which node i is in the component.
#
# Return the maximum number of edges you can delete, such that every connected component in the tree has the same value.
#
# Example:
# Input: nums = [6,2,2,2,6], edges = [[0,1],[1,2],[1,3],[3,4]] 
# Output: 2 
# Explanation: The above figure shows how we can delete the edges [0,1] and [3,4]. The created components are nodes [0], [1,2,3] and [4]. The sum of the values in each component equals 6. It can be proven that no better deletion exists, so the answer is 2.
#
# Constraints:
# 1 <= n <= 2 * 104
# 	nums.length == n
# 	1 <= nums[i] <= 50
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= edges[i][0], edges[i][1] <= n - 1
# 	edges represents a valid tree.
#
# Helpful references (internal KB):
# - Number of divisors / sum of divisors (number, counting, enumeration)
#   • When to use: Use this approach when you need to calculate the total count or sum of all positive divisors for a given integer, typically by leveraging its prime factorization.
#   • Idea: The number of divisors d(n) and sum of divisors sigma(n) are arithmetic functions derived from the prime factorization of an integer n. Both can be computed efficiently by first finding prime factors and their exponents, resulting in an O(sqrt(N)) or O(log N) complexity with precomputed primes.
#   • Invariants: The current count of divisors is the product of (exponent + 1) for all prime factors found so far.; The current sum of divisors is the product of (1 + p + ... + p^e) for all prime factors found so far.
#   • Tips: Precompute primes using a sieve for efficiency when dealing with multiple queries or large numbers.; For sum of divisors, the formula is sigma(n) = product((1 + p_i + ... + p_i^e_i)) for each prime factor p_i^e_i.
#   • Pitfalls: Forgetting to handle n=1 correctly, which has one divisor.; Integer overflow when calculating sums or products of large powers, especially for sum of divisors.
# - Number of divisors / sum of divisors (number, counting, enumeration)
#   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
#   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
#   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
#   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
#   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
# - Integer factorization (number, array, enumeration, sieve, counting)
#   • When to use: Use when needing to find the prime factors of a composite number, especially for relatively small numbers or as a base case for more advanced algorithms.
#   • Idea: This algorithm finds the prime factorization of an integer by iteratively dividing it by its smallest prime factors. It typically checks divisors up to the square root of the number, achieving an O(sqrt(N)) time complexity.
#   • Invariants: The product of all found prime factors multiplied by the current remaining number equals the original input number.; All prime factors found so far are less than or equal to the current divisor being tested.
#   • Tips: Perform a primality test first to avoid unnecessary factorization attempts.; Only check divisors up to the square root of the number.
#   • Pitfalls: Trial division is pseudo-polynomial time, making it inefficient for very large numbers.; Forgetting to handle the case where the remaining number after division is itself a prime greater than its original square root.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def componentValue(self, nums, edges):
        """
        :type nums: List[int]
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, deque

        n = len(nums)
        total_sum = sum(nums)
        graph = defaultdict(list)

        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        def bfs(start, target):
            visited = set()
            queue = deque([start])
            component_sum = 0

            while queue:
                node = queue.popleft()
                if node in visited:
                    continue
                visited.add(node)
                component_sum += nums[node]

                for neighbor in graph[node]:
                    if neighbor not in visited:
                        queue.append(neighbor)

            return component_sum == target

        for k in range(n - 1, 0, -1):
            if total_sum % (k + 1) != 0:
                continue

            target_value = total_sum // (k + 1)
            visited = set()
            valid_components = 0

            for i in range(n):
                if i not in visited:
                    if bfs(i, target_value):
                        valid_components += 1
                    else:
                        break

            if valid_components == k + 1:
                return k

        return 0