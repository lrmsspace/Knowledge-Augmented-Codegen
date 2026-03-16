# Source: https://leetcode.com/problems/maximum-prime-difference/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# Return an integer that is the maximum distance between the indices of two (not necessarily different) prime numbers in nums.
#
# Example:
# Input: nums = [4,2,9,5,3]
#
# Output: 3
#
# Explanation: nums[1], nums[3], and nums[4] are prime. So the answer is |4 - 1| = 3.
#
# Constraints:
# 1 <= nums.length <= 3 * 105
# 	1 <= nums[i] <= 100
# 	The input is generated such that the number of prime numbers in the nums is at least one.
#
# Helpful references (internal KB):
# - Sieve of Eratosthenes (array, sieve, enumeration)
#   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
#   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
#   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
#   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Minimum spanning tree - Prim's algorithm (graph, mst-prim, greedy)
#   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, undirected, weighted graph. It is often preferred for dense graphs due to its O(V^2) or O(E log V) complexity.
#   • Idea: Prim's algorithm is a greedy algorithm that builds a minimum spanning tree by iteratively adding the cheapest edge connecting a vertex in the growing tree to one outside it. It typically runs in O(E log V) time with a binary heap or O(V^2) with an adjacency matrix.
#   • Invariants: The set of vertices already included in the MST forms a connected component.; For any vertex not yet in the MST, its associated key/distance stores the minimum weight of an edge connecting it to a vertex already in the MST.
#   • Tips: Use a priority queue to efficiently retrieve the minimum weight edge connecting to the MST.; Initialize distances for all vertices to infinity, except the starting vertex (0).
#   • Pitfalls: Not suitable for disconnected graphs; it will only find an MST for the component of the starting vertex.; Forgetting to handle edge cases like graphs with no edges or a single vertex.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumPrimeDifference(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def is_prime(n):
            if n <= 1:
                return False
            for i in range(2, int(n**0.5) + 1):
                if n % i == 0:
                    return False
            return True

        primes_indices = [i for i, num in enumerate(nums) if is_prime(num)]
        if not primes_indices:
            return 0

        return primes_indices[-1] - primes_indices[0]