# Source: https://leetcode.com/problems/count-pairs-that-form-a-complete-day-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array hours representing times in hours, return an integer denoting the number of pairs i, j where i < j and hours[i] + hours[j] forms a complete day.
#
# A complete day is defined as a time duration that is an exact multiple of 24 hours.
#
# For example, 1 day is 24 hours, 2 days is 48 hours, 3 days is 72 hours, and so on.
#
# Example:
# Input: hours = [12,12,30,24,24]
#
# Output: 2
#
# Explanation: The pairs of indices that form a complete day are (0, 1) and (3, 4).
#
# Constraints:
# 1 <= hours.length <= 5 * 105
# 	1 <= hours[i] <= 109
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Garner's algorithm
#  (number, array, enumeration)
#   • When to use: Use when reconstructing a large integer from a system of congruences with pairwise coprime moduli, offering an alternative to the direct Chinese Remainder Theorem approach.
#   • Idea: Garner's algorithm efficiently reconstructs an integer from its remainders modulo a set of pairwise coprime numbers, by computing its mixed radix representation coefficients. It typically runs in O(k^2 log M) time, where k is the number of moduli and M is the maximum modulus, assuming modular inverse takes log M time.
#   • Invariants: At the start of iteration j, the partial sum $V_{j-1}$ satisfies $V_{j-1} \equiv a_i \pmod{p_i}$ for all $i < j$.; For each iteration j, the coefficient $x_j$ is uniquely determined in the range $[0, p_j - 1]$.
#   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Precompute modular inverses for efficiency, especially if many are needed.
#   • Pitfalls: Incorrectly calculating modular inverses, leading to wrong coefficients.; Not handling large intermediate products, which can cause integer overflow.
# - Finding repetitions (string, array, z-function, enumeration)
#   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
#   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
#   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
#   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
#   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countCompleteDayPairs(self, hours):
        """
        :type hours: List[int]
        :rtype: int
        """
        mod_count = {}
        for h in hours:
            mod = h % 24
            mod_count[mod] = mod_count.get(mod, 0) + 1

        total_pairs = 0

        # Pairs where both elements are 0 mod 24
        if 0 in mod_count:
            count_0 = mod_count[0]
            total_pairs += count_0 * (count_0 - 1) // 2

        # Pairs where both elements are 12 mod 24
        if 12 in mod_count:
            count_12 = mod_count[12]
            total_pairs += count_12 * (count_12 - 1) // 2

        # Pairs where one element is i and the other is (24 - i)
        for i in range(1, 12):
            if i in mod_count and (24 - i) in mod_count:
                total_pairs += mod_count[i] * mod_count[24 - i]

        return total_pairs