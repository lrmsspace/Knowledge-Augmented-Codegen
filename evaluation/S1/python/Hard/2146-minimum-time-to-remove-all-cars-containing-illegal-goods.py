# Source: https://leetcode.com/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed binary string s which represents a sequence of train cars. s[i] = '0' denotes that the ith car does not contain illegal goods and s[i] = '1' denotes that the ith car does contain illegal goods.
#
# As the train conductor, you would like to get rid of all the cars containing illegal goods. You can do any of the following three operations any number of times:
#
#
# 	Remove a train car from the left end (i.e., remove s[0]) which takes 1 unit of time.
# 	Remove a train car from the right end (i.e., remove s[s.length - 1]) which takes 1 unit of time.
# 	Remove a train car from anywhere in the sequence which takes 2 units of time.
#
#
# Return the minimum time to remove all the cars containing illegal goods.
#
# Note that an empty sequence of cars is considered to have no cars containing illegal goods.
#
# Example:
# Input: s = "1100101"
# Output: 5
# Explanation: 
# One way to remove all the cars containing illegal goods from the sequence is to
# - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
# - remove a car from the right end. Time taken is 1.
# - remove the car containing illegal goods found in the middle. Time taken is 2.
# This obtains a total time of 2 + 1 + 2 = 5. 
#
# An alternative way is to
# - remove a car from the left end 2 times. Time taken is 2 * 1 = 2.
# - remove a car from the right end 3 times. Time taken is 3 * 1 = 3.
# This also obtains a total time of 2 + 3 = 5.
#
# 5 is the minimum time taken to remove all the cars containing illegal goods. 
# There are no other ways to remove them with less time.
#
# Constraints:
# 1 <= s.length <= 2 * 105
# 	s[i] is either '0' or '1'.
#
# Helpful references (internal KB):
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - String Hashing (string, number, hashing, prefix-sum)
#   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
#   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
#   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
#   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
#   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumTime(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        s = s + s  # Duplicate the string to handle circular cases
        dp = [[0] * (2 * n) for _ in range(2 * n)]

        # Base case: single cars
        for i in range(2 * n):
            dp[i][i] = 1 if s[i] == '1' else 0

        # Fill the DP table
        for length in range(2, n + 1):  # Only need to consider lengths up to n
            for l in range(0, 2 * n - length + 1):
                r = l + length - 1
                if s[l] == '1' and s[r] == '1':
                    dp[l][r] = min(dp[l + 1][r], dp[l][r - 1]) + 1
                elif s[l] == '1':
                    dp[l][r] = dp[l + 1][r] + 1
                elif s[r] == '1':
                    dp[l][r] = dp[l][r - 1] + 1
                else:
                    dp[l][r] = min(dp[l + 1][r], dp[l][r - 1])

        # Find the minimum time among all intervals of length n
        min_time = float('inf')
        for i in range(n):
            min_time = min(min_time, dp[i][i + n - 1])

        return min_time