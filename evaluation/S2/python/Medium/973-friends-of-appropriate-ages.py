# Source: https://leetcode.com/problems/friends-of-appropriate-ages/   |   Difficulty: Medium
#
# Problem Description:
# There are n persons on a social media website. You are given an integer array ages where ages[i] is the age of the ith person.
#
# A Person x will not send a friend request to a person y (x != y) if any of the following conditions is true:
#
#
# 	age[y] <= 0.5 * age[x] + 7
# 	age[y] > age[x]
# 	age[y] > 100 && age[x] < 100
#
#
# Otherwise, x will send a friend request to y.
#
# Note that if x sends a request to y, y will not necessarily send a request to x. Also, a person will not send a friend request to themself.
#
# Return the total number of friend requests made.
#
# Example:
# Input: ages = [16,16]
# Output: 2
# Explanation: 2 people friend request each other.
#
# Constraints:
# n == ages.length
# 	1 <= n <= 2 * 104
# 	1 <= ages[i] <= 120
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Euler's totient function
#  (array, number, enumeration)
#   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
#   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
#   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
#   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
#   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
# - Search for a pair of intersecting segments (tree, geometry, sweep-line, counting)
#   • When to use: Use this algorithm to efficiently determine if any pair of line segments in a given set intersect. It is particularly effective for detecting geometric overlaps in a 2D plane.
#   • Idea: This algorithm processes segments by sweeping a vertical line across the plane, maintaining an ordered set of active segments to efficiently check for intersections with neighbors. It achieves an optimal time complexity of O(N log N).
#   • Invariants: The sweep line always moves from left to right, processing events in increasing x-coordinate order.; The set of active segments contains all segments currently intersected by the sweep line, ordered by their y-coordinate at the sweep line's current x-position.
#   • Tips: Process events at the same x-coordinate by adding segments before removing them to catch vertex intersections.; Use a balanced binary search tree (e.g., `std::set`) to maintain active segments, ordered by their y-coordinate.
#   • Pitfalls: Incorrect event ordering (e.g., removing before adding) can lead to missing intersections at shared endpoints.; Floating point precision issues can cause incorrect intersection detection or ordering of segments.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numFriendRequests(self, ages):
        """
        :type ages: List[int]
        :rtype: int
        """
        count = [0] * 121
        for age in ages:
            count[age] += 1

        total_requests = 0
        for A in range(15, 121):
            if count[A] == 0:
                continue
            for B in range(15, A + 1):
                if count[B] == 0:
                    continue
                if B <= 0.5 * A + 7:
                    continue
                if B > A:
                    continue
                if B > 100 and A < 100:
                    continue

                total_requests += count[A] * count[B]
                if A == B:
                    total_requests -= count[A]

        return total_requests