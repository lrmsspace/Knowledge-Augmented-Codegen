# Source: https://leetcode.com/problems/prime-in-diagonal/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed two-dimensional integer array nums.
#
# Return the largest prime number that lies on at least one of the diagonals of nums. In case, no prime is present on any of the diagonals, return 0.
#
# Note that:
#
#
# 	An integer is prime if it is greater than 1 and has no positive integer divisors other than 1 and itself.
# 	An integer val is on one of the diagonals of nums if there exists an integer i for which nums[i][i] = val or an i for which nums[i][nums.length - i - 1] = val.
#
#
#
#
# In the above diagram, one diagonal is [1,5,9] and another diagonal is [3,5,7].
#
# Example:
# Input: nums = [[1,2,3],[5,6,7],[9,10,11]]
# Output: 11
# Explanation: The numbers 1, 3, 6, 9, and 11 are the only numbers present on at least one of the diagonals. Since 11 is the largest prime, we return 11.
#
# Constraints:
# 1 <= nums.length <= 300
# 	nums.length == numsi.length
# 	1 <= nums[i][j] <= 4*106
#
# Helpful references (internal KB):
# - Primality tests (number, enumeration, simulation)
#   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
#   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
#   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
#   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
#   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Minimum spanning tree - Prim's algorithm (graph, matrix, array, mst-prim, greedy)
#   • When to use: When you need to find a minimum spanning tree in a connected, weighted graph, especially efficient for dense graphs or when starting from an arbitrary vertex.
#   • Idea: Prim's algorithm is a greedy algorithm that constructs a Minimum Spanning Tree (MST) by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside it. It typically runs in O(E log V) with a priority queue or O(V^2) with an adjacency matrix.
#   • Invariants: The set of edges chosen so far forms a tree (no cycles) and connects a subset of vertices.; At each step, the chosen edge is the minimum weight edge connecting a vertex in the current MST to a vertex outside it.
#   • Tips: Initialize distances (or minimum edge weights) for all vertices not in the MST to infinity.; Use a priority queue to efficiently retrieve the minimum weight edge connecting to the current MST.
#   • Pitfalls: Failing to correctly update edge weights to neighbors when a new vertex is added to the MST.; Not handling disconnected graphs, which will result in only an MST for the starting component.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def diagonalPrime(self, nums):
        """
        :type nums: List[List[int]]
        :rtype: int
        """
        def is_prime(n):
            if n <= 1:
                return False
            if n == 2:
                return True
            if n % 2 == 0:
                return False
            for i in range(3, int(n**0.5) + 1, 2):
                if n % i == 0:
                    return False
            return True

        max_prime = 0
        n = len(nums)

        for i in range(n):
            # Check primary diagonal
            if is_prime(nums[i][i]):
                max_prime = max(max_prime, nums[i][i])
            # Check secondary diagonal
            if is_prime(nums[i][n - i - 1]):
                max_prime = max(max_prime, nums[i][n - i - 1])

        return max_prime