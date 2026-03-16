# Source: https://leetcode.com/problems/largest-component-size-by-common-factor/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array of unique positive integers nums. Consider the following graph:
#
#
# 	There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
# 	There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
#
#
# Return the size of the largest connected component in the graph.
#
# Example:
# Input: nums = [4,6,15,35]
# Output: 4
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	1 <= nums[i] <= 105
# 	All the values of nums are unique.
#
# Helpful references (internal KB):
# - Sieve of Eratosthenes (array, sieve, enumeration)
#   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
#   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
#   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
#   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
# - Finding Bridges Online (graph, tree, union-find, counting)
#   • When to use: Use when you need to dynamically track bridges and 2-edge-connected components in a graph as edges are added. It efficiently updates the graph structure and bridge count in an online fashion.
#   • Idea: This algorithm maintains 2-edge-connected components and bridges in a graph as edges are added, using a Union-Find structure to manage components and a forest to represent the relationships between them. It typically achieves near-amortized constant time per edge addition.
#   • Invariants: Each 2-edge-connected component is represented by a single root in the Union-Find structure.; The set of bridges forms a forest where each node is a 2-edge-connected component.
#   • Tips: Represent 2-edge-connected components using Union-Find for efficient merging.; Maintain a forest where nodes are 2-edge-connected components and edges are bridges.
#   • Pitfalls: Incorrectly identifying when an edge forms a cycle with existing bridges.; Failing to update the bridge count accurately when bridges are removed.
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
    def largestComponentSize(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # Step 1: Find the maximum number to determine the size of the sieve
        max_num = max(nums)

        # Step 2: Create a sieve to find the smallest prime factor for each number
        spf = list(range(max_num + 1))  # spf[i] will hold the smallest prime factor of i
        for i in range(2, int(max_num**0.5) + 1):
            if spf[i] == i:  # i is prime
                for j in range(i * i, max_num + 1, i):
                    if spf[j] == j:
                        spf[j] = i

        # Step 3: Union-Find (Disjoint Set Union) implementation
        parent = list(range(len(nums)))
        size = [1] * len(nums)

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]  # Path compression
                x = parent[x]
            return x

        def union(x, y):
            root_x = find(x)
            root_y = find(y)
            if root_x != root_y:
                if size[root_x] < size[root_y]:
                    root_x, root_y = root_y, root_x
                parent[root_y] = root_x
                size[root_x] += size[root_y]

        # Step 4: Map each number to its index and union based on common factors
        num_to_index = {num: idx for idx, num in enumerate(nums)}
        for num in nums:
            factors = set()
            x = num
            while x > 1:
                factors.add(spf[x])
                x //= spf[x]
            for factor in factors:
                if factor in num_to_index:
                    union(num_to_index[num], num_to_index[factor])

        # Step 5: Find the largest component size
        return max(size)